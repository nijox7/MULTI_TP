# Compte-rendu TP3

## C - Application logicielle

### C1
(20*2*4 + 48)*2 + 20*2*4 = 576 octets
seg_data_base + 576
Première instruction main -> seg_data_base + 576  = (0x01000000)16 + (576)10
Première instruction loop -> seg_data_base + 4 = (0x01000004)16 + (576)10
<!-- à revoir TODO-->

### C2
A: seg_data_base
B: seg_data_base + 20*2*4+48
C: seg_data_base + (20*2*4+48)*2
<!--a verifier TODO -->

### C3
Pour ne pas gaspiller de cycle, comme lors d'un bne sur l'architecture Mips32 on a un cycle de nop après chaque branchement, on le remplace par une instruction utile.
<!-- A préciser, être sur TODO-->

### C4
<!-- A FAIRE TODO-->
Calculer le nombre de cycle (compter les dépendance etc..)
=> 7 cycles?


## D - Fonctionnement du cache instruction

### D1

BYTE: 4 bits car 16 octets à choisir
SET: 3 bits car 8 lignes à choisir
TAG: 25 bits car 1 seul way possible?
<!-- à revoir TODO -->

0x00400000 correspond donc à:
TAG=0x8000
SET=0x0
BYTE=0x0 


### D2
Les instructions qui ont déclenché un MISS pour atteindre la fin de la première itération de la boucle de la fonction main sont:
lw   $10,    0($8)         # $10 <= A[i]
et
add  $12,    $10,     $11  # $12 <= A[i]+B[i]

### D3
Le cache reste dans le même état et ne fait pas de miss.
<!-- pas sur --TODO-->

### D4
Le MISS_SELECT est indispensable pour les caches qui ne sont pas à correspondance directe.

### D6
Activation de RESETN provoque le passage à l'état IDLE.
L'autre effet doit être d'effacer complètement le cache d'instructions.


## E - Fonctionnement du cache de données
