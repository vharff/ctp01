import pylab as plt

# plots
def gridme(p0,p1,func,chi2=False):
    """
    Tabule une fonction évaluée sur une grille 2D definie par les tableaux p0 et p1
    """
    lkarr = np.zeros((len(p0),len(p1)))
    for i,pp in enumerate(p0):
        lkarr[i,:]=np.array([func([pp,py]) for py in p1]).flat[:]
    if chi2:
      mx = np.min(lkarr)
      lkarr = np.exp(-.5*(lkarr-mx))
    return lkarr

def pretty_contour(x,y,z,get_contour_levels, levels=(0.68,0.95,0.99),*args,**kargs):
  """
  Trace les contours 2D du tableau z contenant 68%, 95% and 99% des points
  """
  lvls = [get_contour_levels(z,ll) for ll in levels]
  dvls = dict(zip(lvls,["%.0f%%"%(v*100) for v in levels]))
  if "colors" not in kargs:
    kargs["colors"]="black"
  CS=plt.contour(x, y, z,lvls[::-1],*args,**kargs)
  plt.gca().clabel(CS, fmt=dvls,inline=1, fontsize=10)


import numpy as np

class UndefinedChi2(ZeroDivisionError):
  pass

class chain:
  # une classe simple pour une chaîne MCMC
  def __init__(self,pos,chi2f):
    self.nstep = 0 # nombre de pas 
    self.nval = 0 # nombre de pas différents nval<=nstep
    self.maxval=1000 # taille du buffer
    self.ndim=len(pos) # nombre de dimension de l'espace des paramètres
    self.weight = np.zeros(self.maxval) # poids de chaque pas différent. nstep = sum(weight)
    self.chain = np.zeros((self.maxval,self.ndim)) # positions dans l'espace des paramètres
    self.chi2 = np.zeros(self.maxval) # log vraisemblance à chaque position
    self.accept(pos,chi2f)

  def accept(self,pos,chi2f):
    if self.nval==self.maxval:
      weight = np.zeros(self.maxval*2) # poids de chaque pas différent. nstep = sum(weight)
      chain = np.zeros((self.maxval*2,self.ndim)) # positions dans l'espace des paramètres
      chi2 = np.zeros(self.maxval*2) # log vraisemblance à chaque position
      weight[:self.maxval] = self.weight
      chain[:self.maxval] = self.chain
      chi2[:self.maxval] = self.chi2
      self.weight = weight
      self.chain = chain
      self.chi2 = chi2
      self.maxval*=2
    self.weight[self.nval] = 1
    self.chi2[self.nval] = chi2f
    self.chain[self.nval] = pos
    self.nval+=1
    self.nstep+=1
  def reject(self):
    self.weight[self.nval-1] += 1
    self.nstep+=1

  def integrate(self,func):
    return np.sum(self.weight*[func(self.chain[i]) for i in range(self.nval)])/self.nstep
  
  # calcule la moyenne de la chaîne
  def mean(self):  
    return np.sum(self.chain[:self.nval]*self.weight[:self.nval,np.newaxis],axis=0)/self.nstep
    # On peut aussi utiliser np.average(chain[:,2:],weigths=chain[:,0])


  # calcule la covariance de la chaîne
  def covariance(self):
    mean = self.mean()
    # On pourrait faire sans boucle, mais cela nécessiterait un tableau inutilement large!
    res = np.zeros((self.ndim,self.ndim))
    normalization = 1.*self.nstep
    pars0 = self.chain[:self.nval] - mean[np.newaxis,:]
    for i in range(self.ndim):
      res[i,i] = np.sum(pars0[:,i]*pars0[:,i]*self.weight[:self.nval],axis=0)/normalization
      for j in range(i+1,self.ndim):
        res[i,j] = np.sum(pars0[:,i]*pars0[:,j]*self.weight[:self.nval],axis=0)/normalization
        res[j,i] = res[i,j]
    return res
    # On peut aussi utiliser np.cov(chain[:,2:],fweights=chain[:,0])

  # calcule l'acceptance
  def acceptance(self):
    return (1.*self.nval)/self.nstep

  def minmax(self):
    # retourne l'intervalle des paramètres
    return np.array([np.min(self.chain[:self.nval],axis=0),np.max(self.chain[:self.nval],axis=0)])

  def minmax_range(self,i,ni):
    mima = self.minmax()
    return np.linspace(mima[0,i],mima[1,i],ni)


  def regrid2d(self,i,j,ibins,jbins):
    """
    Calcule une approximation 2D en utilisant une KDE appropriée pour le tracé de contours
    pour les ièmes et jèmes paramètres
    """
    import scipy.stats.kde as kde
    #self.chain[:,i]
    #self.weight
    dens = kde.gaussian_kde([self.chain[:self.nval,i],self.chain[:self.nval,j]],weights=self.weight[:self.nval])
    if type(ibins)==int:
      ibins = self.minmax_range(i,ibins)
    if type(jbins)==int:
      jbins = self.minmax_range(j,jbins)

    mcarr = gridme(ibins,jbins,dens)
    return ibins,jbins,mcarr

  def plot_brown(self,i,j):
    plt.plot(self.chain[:self.nval,i],self.chain[:self.nval,j],marker=".",ms=4,lw=.7,c="lightblue",alpha=.4,zorder=-100)

# routine MCMC
def mcmc(mcmc_step,chi2_func,xi,SigmaProp,nstep=1000,extra=()):
  """ 
  chi2_func est la fonction chi2
  xi est le point de départ dans l'espace des paramètres
  SigmaProp est la matrice de covariance utilisée pour proposer un nouveau point
  """
  xi = np.array(xi)
  chi2i = chi2_func(xi) # calcule le chi2 initial
  ch = chain(xi,chi2i)
  for i in range(nstep):
    ac,chi2f,xf = mcmc_step(chi2_func,xi,SigmaProp,extra,chi2i) # faire un pas
    if ac: 
      ch.accept(xf,chi2f)
      chi2i = chi2f
      xi = xf      
    else: # refuse !
      ch.reject()
  return ch


def make_chi2_banana(prs0,sig,banane):
  # log-vraisemblence d'une gaussienne non-normalisée générique
  siginv = np.linalg.inv(sig)
  prs0 = np.array(prs0)
  def chi2(prs):
    pp = prs-prs0
    pp[1]=pp[1]-banane*(pp[0]**2-sig[0,0])
    return np.dot(pp,np.dot(siginv,pp)) # log-vraisemblance : vraisemblance = exp(-0.5 chi^2)
  return chi2

def make_chi2_gauss(prs0,sig):
  return make_chi2_banana(prs0,sig,0)

sig = np.array([[1,1.5],[1.5,4]])
test_gauss = make_chi2_banana([1,-3],sig,0)
test_banana = make_chi2_banana([0,-2],sig,.5)

def _mcmc_step(chi2,xi,SigmaProp,extra=(),chi2_0=None):
  """
  chi2_func calcule le chi2 de sorte que la fonction de vraisemblance soit exp(-.5*chi2)
  xi est le point actuel dans l'espace des paramètres
  SigmaProp est la matrice de covariance utilisée pour proposer un nouveau point
  """

  if chi2_0==None:          
    chi2_0 = chi2(xi,*extra) # calculer la vraisemblance initiale si nécessaire

  #### --------------------------------------
  #### Exercice : proposer un nouveau point ici, en utilisant xi et SigmaProp 
  # xf = 
  #### --------------------------------------
  xf = np.random.multivariate_normal(xi,SigmaProp,1)[0] # proposer un nouveau point
  try:
    chi2_1 = chi2(xf,*extra)
  except:
    # refuser proprement le point s'il est en dehors du domaine
    # de validité des paramètres
    return False,chi2_0,xi

  #### --------------------------------------
  #### Exercice : Vérifier l'acceptance ici !
  # accept = SOMECONDITION (boolean)
  #### --------------------------------------
  accept = np.random.uniform()<np.exp(-.5*(chi2_1-chi2_0))

  if accept:    # teste l'acceptance 
    return True,chi2_1,xf # accepte
  return False,chi2_0,xi # refuse

def get_level(prob_arr,v):
 # première étape, reclasser une version monodimensionnelle de la grille par ordre décroissant.
  sort_grid = prob_arr.flat[:]*1.
  sort_grid.sort() # par ordre croissant
  sort_grid = sort_grid[::-1] # par ordre décroissant

  # on calcule maintenant la cumulative
  cis=np.cumsum(sort_grid)
  nrm = cis[-1] # on calcule la normalisation
  cis/=nrm # et on renormalise
  # la fonction searchsorted() renvoie l'index ou se situerait un nombre dans un tableau ordonné
  # cis est ordonné par construction
  a_pv = np.searchsorted(cis,v) 
  # a_pv est l'indice pour lequel cis=v, 
  # c'est aussi l'indice de la dernière valeur ajoutée pour estimer la cumulative
  levl = sort_grid[a_pv]
  return levl
