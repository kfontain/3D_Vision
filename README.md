Projet Technologique 6 : Vision 3D pour robots

Camille CLAVAUD Geoffrey MEILHAN Kenji FONTAINE Mohamed ALAMI

-----
Rendu pour la séance du 17/02/2017

Fait :
- Regarder les problèmes présents sur les images. (module calib3d)
Les images doivent être sur le même plan vertical.
La caméra nécessite une calibration. Détermination des paramètres de la caméra ?
en utilisant des échequiers.
Corriger la distorition crée par la caméra. (lens distortion)

Todo :
- Implémenter les fonctions liées à la calibration. (beaucoup d'arguments...)

----
Rendu pour la séance du 03/03/2017

Fait :
- Créer un script permettant l'acquisition d'une image. Le résultat est le
fichier "test.png". Notre algorithme de calcul de carte de disparité prend une
"double-image" en paramètre. (comme l'image "test.png")

Todo :
- Automatiser l'acquisition d'image.
- Automatiser le calcul de carte de disparité.

-----
Rendu pour la séance du 10/03/2017

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
