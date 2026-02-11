# Compte-rendu TP2

## C - Modélisation de l'architecture matérielle

### C1
1 mot = 32 bits = 4 octets
ligne cache = 4 mots
tampon d'écritures postées = 8 mots
capacité cache = 1k octet

On a donc probablement 1024 bits dans le cache et 128 bits par ligne donc:
1024/128 = 8 bits par ligne.
=> number of sets

Pas d'associativité, 
=> number of associative ways = 0

### C2
Le segment seg_reset n'est pas assigné au même composant matériel car c'est un segment mémoire qui ne doit pas disparaître hors-tension puisqu'il est nécessaire au boot de l'architecture.

### C3
Le segment tty doit être non cachable car il correspond à l'écran et au clavier. Il n'y a donc pas d'intérêt à cacher les données puisqu'elles ne sont pas predictibles, étant entrées par l'utilisateur.
Implémenter un cache pour ce composant ne serait pas rentable.

### C4
?
<!-- TO DO -->

## D - Système d'exploitation: GIET

### D1
Le programme utilisateur lors d'un appel système fournit au système d'exploitation:
- le numéro de l'appel système qui permettra de l'identifier
- la liste des arguments de l'appel

Pour cela le GIET effectue un syscall en assembleur en spécifiant les bonnes valeurs aux registres.

### D2
_cause_vector contient 16 fonctions qui chacune une exception, il est indexés par les numéros d'exception. Ces fonctions sont appelée lors de leur exception respective.
Il est initialisé dans exc_handler.c.

_syscall_vector contient les 32 appels systèmes que l'on peut faire en tant qu'utilisateur. Il est indexé par leur numéro respectif. Ces fonctions sont appelée lors de leur appel système respectif.
Il est initialisé dans sys_handler.c.

### D3
proctime() -> syscall -> _sys_handler -> _syscall_vector[0] -> _proctime -> mfc0

### D4
On aura: 
1 cycle pour proctime,
24 cycles pour _sys_handler
mfc0 -> 1 cycles

On aura donc environ 26 cycles lors de cet appel système.



## E - Génération du code binaire

### E1
Le code boot doit s'exécuter en modes superviseur car:
- On a besoin d'initialiser les périphériques
- D'accéder à la mémoire
- De faire des appels systèmes qui ne sont pas disponibles en utilisateur
- Un utilisateur ne doit pas pouvoir modifier le boot de la machine car celà pourrait l'endommager

### E2


## Notes
la => "load address"
mfc0: "move from coprocessor 0
SR register -> state register
eret -> exception return