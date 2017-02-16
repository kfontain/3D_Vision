Projet Technologique 6 : Vision 3D pour robots

Camille CLAVAUD Geoffrey MEILHAN Kenji FONTAINE Mohamed ALAMI

-----
Rendu pour la séance du 03/02/2017

Fait :
- Implémenter 2 caméras liées sur Unity.
- Créer un modèle humanoïde sur Unity.
- Créer un script permettant de déplacer un objet sur Unity. (fichier move.cs)
- Tester l'algorithme de carte de disparité sur les images obtenues sur Unity.
Ces images sont visibles dans le dossier "Test".

Todo :
- Décider d'une distance fixe entre les caméras afin d'implémenter l'algorithme
calculant la carte de profondeur.

-----
Rendu pour la séance du 10/02/2017

Fait :
- Faire des tests de cartes de disparités sur différentes distance sur Unity.
Les fichiers sont disponibles dans le dossier /unity/simtest.
- Implémenter un prototype de l'algorithme de calcul de carte de profondeur.
L'algorithme est fonctionnel algorithmiquement. La fonction prend en paramètre
une carte de disparité en paramètre et retourne une carte de même taille en
effectuant des calculs sur chacun des pixels.

Todo :
- Décider des paramètres de la formule de calcul de la carte de profondeur
(écart caméra, distance focale, etc...).
- Améliorer l'algorithme de calcul de la carte de profondeur en évitant les
erreurs (division par 0).

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
