Projet Technologique 6 : Vision 3D pour robots

Camille CLAVAUD Geoffrey MEILHAN Kenji FONTAINE Mohamed ALAMI

-----

Rendu pour la séance du 17/03/2017

Fait :
- Automatiser la prise de captures d'écran sous Unity tout en déplacant le
personnage et les caméras.
- Automatiser le calcul de carte de disparité sur chacune des captures d'écran
ainsi obtenues.
- L'automatisation est faite en passant par des fichiers images sur le HDD.
Les chemins d'accès étant codés en durs dans le code, cela ne marchera pas sur
d'autre machine.
- Affiner les paramètres de l'algorithme de calcul de cartde de disparité.

Séance robot :
- D'après nos simulations, une bonne distance entre les caméras stéréo serait
aux environs de ~6cm. Le but de la séance serait d'essayer plusieurs écartements
proches de cette valeur sur le robot. En commençant par 5, 6 et 7cm, puis en
procédant par tatonnement au vu des résultats.

-----

Rendu pour la séance du 24/03/2017

Nous avons appliquer notre algorithme de calcul de carte de disparité sur les
images que nous avons prises lors de la séance avec le robot. Après différents
tests avec de multiples paramètres, multiples écarts, nous avons constaté que
notre algorithme n'était pas efficace.
Nous avons donc décidé d'implémenter un nouvel algorithme utilisant l'algorithme
StereoSGBM (précédemment StereoBM). Nous voulons également implémenter un tuner
qui nous permettrait d'ajuster les paramètres de StereoSGBM sans avoir à repasser
par une recompilation du code.
