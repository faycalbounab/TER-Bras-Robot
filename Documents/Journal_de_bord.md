# Journal de bord

### Semaine du 04/03/2019 
Nous avons recuperé le bras robotique aupres de nos encadrants, nous allons commencer par calibrer le 
bras avant de réfléchir au jeux que nous allons étudier. Nous pensons déjà travailler sur le jeu de société Takenoko et le jeu 
d'échec.
Dans ce TER nous ferons une étude sur les différents bras robotiques que nous aurions pu avoir et voir aussi la différence entre 
un arduino et une raspberry.

### Semaine du 11/03/2019
Cette semaine nous avons démonté et remonté tous les moteurs du bras robotique afin de les calibrer. 
Après avoir fini l'assemblage nous avons remarqué que ses mouvements étaient trop brusques de ce fait nous avons diminué la 
vitesse de ses mouvements.
Pour la semaine prochaine on essayera de lui faire prendre un objet quelconque pour avoir une vision plus précise des 
possibilités offertes pas le robot

### Semaine du 19/03/2019
Cette semaine nous avons réussi à faire attraper et reposer une pièce du jeu d'échecs sans la faire 
retomber.
Pour la semaine prochaine on essaiera de faire des calculs sur les angles pour faire en sorte que les différentes parties 
(surtout les parties gérées par le moteur 2,3,4) du robot ne se gênent pas lors du mouvement. 


### Semaine du 25/03/2019
Cette semaine nous avons préparé un quadrillage pour positionner en (x,y) le bras dans l'espace. Puis, nous avons commencé à calculer les angles de déplacement des moteurs et leur position initial dans l'espace.
Pour la semaine prochaine nous continuerons sur les calculs afin de les implémenter.

#### Réunion avec Monsieur Rennevier
Nous avons fait une démonstration du bras robotique, il a ainsi fait une prise d'une piece d'échec. Ensuite nous avons vu avec 
Monsieur Rennevier s'il y a la possibilité d'intégrer le wifi à notre carte arduino. Nous allons faire une recherche sur la 
carte wifi à commander et sur les différences entre les raspberrys et notre carte arduino.


### Semaine du 01/04/2019
Cette semaine nous avons fini les calculs des angles(voir fichier Angles), nous avons commencé un système de contrainte(formules) pour avoir le champ d'action du bras robotique.
Pour le découpage du code, nous avons fait une classe servo pour avoir des objets qui correspondent à chacun des servo.

### Semaine du 08/04/2019
Cette semaine nous avons fait un bilan avec Monsieur Malapert, nous avons testé des formules qui permettent de calculer les angles afin d'effectuer un mouvement avec le bras. Nous intégrerons ces formules au code par la suite.
Nous allons aussi faire une étude en parallèle sur la possibilité de passer sur Raspberry.

### Semaine du 15/04/2019
Cette semaine nous avons mis en ligne les calculs via un fichier HTML, qui renvoie vers une page où l'on peut préciser les coordonnées dans l'espace(x,y). Il y a aussi en ligne le début de l'étude des bras robotiques. Nous avons recalibré le Servo4.
Enfin nous avons intégré une fonction de calcul des angles de rotations des 4 premiers Servo.

### Semaine du 22/04/2019
Cette semaine nous avons fait deux fonctions qui renvoient les angles de rotation des 4 premiers Servos sous forme d'un tableau.
Nous lisons les coordonnées x, y et z en entrée standart que nous utilisons pour effectuer un mouvement.

### Semaine du 29/04/2019
Cette semaine nous avons implémenté la prise et la pose d'une pièce (on rentre des positions pour la position de la pronation, le bras se déplace vers la position indiquée, il prend la pièce et se met en position initiale puis attend les nouvelles coordonnées qui indiquent la position où il doit déposer la pièce).
Une diminution des mouvements incontrôlables lors du 1er mouvement.
Et un moyen de contrôler la vitesse des servos.

### Semaine du 06/05/2019
Cette semaine nous avons implémenté deux approches permettant de calculer les mouvements que doivent effectuer les Servos du bras pour se déplacer vers une coordonnée (x,y,z).

### Réunion avec Madame Pelleau
Nous avons présenté les mouvements de prise et pose d'un fou, cependant il y avait encore des imprecisions causées par une méthode de calcul des déplacements qui n'était pas aboutie. Nous avons discuté d'une possible augmentation de la portée du bras grâce à de plus grandes équerres. Nous avons aussi dit que nous avons l'intention de travailler sur le contrôle à distance du bras grâce à une raspberry et l'arduino que Mr Renevier nous a déposé. Mme Pelleau nous a aussi laissé un module wifi pour arduino.

### Semaine du 13/05/2019
Nous avons recalibré les Servos 2 et 3. Nous commençons le travail sur l'arduino wifi et nous avons essayé de faire en sorte de bouger plusieurs servos en même temps mais cela n'est pas possible car le temps de calcule nécessaire est trop important.

### Réunion avec Mr Rennevier
Nous avons présenté les mouvements de prise et pose d'un fou. Nous avons parlé du jeu d'échec, nous allons faire jouer le bras sur un plateau de taille 5x5. Nous essayons d'activer plusieurs servos en même temps et faire fonctionner le wifi. Mr Rennevier nous a conseillé de tester les limites du bras ( précision et portée ), quelles informations intégrer dans le rapport (calibrage du bras ) et comment réaliser une vidéo pour la présentation (durée de la vidéo et présenter une partie en peu de coup).

### Semaine du 20/05/2019
Cette semaine, nous avons repris des mesures plus précises des rotations des Servos (en prenant des photos et avec un rapporteur virtuel). Nous avons testé l'arduino wifi qui fait fonctionner le bras correctement et nous avons commencé à faire un client pour celle-ci.
Nous ferons une pause la semaine prochaine.


### Semaine du 03/06/2019
Cette semaine, nous avons commencé le rapport et nous avons commit une première version du rapport, il n'est pas complet il manquCette semaine, nous avons commencé le rapport et nous avons commis une première version du rapport, il n'est pas complet il manque encore des informations que nous aurons d'ici à la semaine du 10/06. Pour le moment .Pour le moment c'est surtout pour avoir une idée très large de comment il sera.
Nous avons aussi finis les calculs de notre bras pour la précision de celui-ci grace à une méthode que nous avons faites et nous sommes toujours entrain de bosser en parallèle le Wi-fi.

### Réunion avec Mr Rennevier

Nous avons présenté notre client et notre serveur qui est pour le moment opérationnelle il nous reste à l'integrer à notre code afin de tester, nous avons présenté une première version du rapports et pour finir nous avons montré l'amélioration des mouvements du Bras.





