Projet Technologique 6 : Vision 3D pour robots

Camille CLAVAUD Geoffrey MEILHAN Kenji FONTAINE Mohamed ALAMI

***** Rendu pour la séance du 13/01/2017 *****

Fait : Implémentation de l'algorithme de calcul de carte de disparité.

TODO : Implémentation de l'algorithme de calcul de carte de profondeur.

La carte de disparité parait plus sombre que prévu.
Pour la carte de profondeur, nous avons trouvé la formule suivante :
EcartCamera * DistFocale / mapDisp(y,x)

- EcartCamera étant l'écart entre nos deux caméras.
- DistFocale étant la distance focale de nos caméras.
- mapDisp étant la valeur du pixel de la carte de disparité.

Et nous mettons ces valeurs dans chacun des pixel (x,y) pour construire
la carte de pronfondeur.

Cependant, n'ayant pas accès à ces valeurs nous voyons pas comment faire.
