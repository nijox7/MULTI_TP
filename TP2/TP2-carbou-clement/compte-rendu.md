# Compte-rendu TP2

## C - Modélisation de l'architecture matérielle

### C1
size_t icache_ways   = 1; // instruction cache number of ways
size_t icache_sets   = 8; // instruction cache number of sets
size_t icache_words  = 4; // instruction cache number of words per line
size_t dcache_ways   = 1; // data cache number of ways
size_t dcache_sets   = 8; // data cache number of sets
size_t dcache_words  = 4; // data cache number of words per line

### C2
Le segment seg_reset n'est pas assigné au même composant matériel car c'est un segment mémoire qui ne doit pas disparaître hors-tension puisqu'il est nécessaire au boot de l'architecture.

### C3
Le tty est non cachable, car on veut une réponse en temps réel.
On ne peut pas se permettre d'avoir de temps en temps une réponse rapide et de
temps en temps une réponse très lente. Le temps de réponse doit être constant.

Si on rendait le segment tty cachable, cela pourrait créer des incohérences mémoire avec plusieurs processeurs qui utilisent en même temps ce segment.

Implémenter un cache pour ce composant ne serait donc pas rentable.

### C4
Les segments protégés sont:
-seg_code car l'utilisateur ne doit pas pouvoir changer le code sinon il pourrait faire des commandes critiques.
-seg_stack car l'utilisateur doit passer par des appels systèmes s'il veut y accéder.

Cette protection est réalisée par le kernel qui interdit l'accès à ces segments en mode utilisateur.

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
Pour récupérer l'adresse de la fonction main on prend l'adresse de base des données.

### E3
Si les adresses ne sont pas égales entre elles, le logiciel et le matériel ne pourront pas interagir entre eux.
Si le processeur passe une adresse en dehors du code système exécutable, elle sera considérée comme invalide par l'esclave.

### E4
seg_reset possède le code du boot.
seg_kcode possède le code du logiciel et le GIET.


<!-- 
REMPLACER 
mipsel-unknown-elf-objdmp -D sys.bin > sys.bin.txt
PAR
mipsel-unknown-elf-objdump -D sys.bin > sys.bin.txt
                       ^
-->

### E5
seg_reset a une taille de 9 instructions.
seg_kcode a une taille d'environ 2200 instructions.

### E7
C'est la fonction tty_getc() qui contient la boucle d'attente.
Tant que ret=0 (tant que aucun caractère n'a été transmis par _tty_read), la fonction boucle.
C'est tty_getc qui contient cette boucle car si tty_read était bloquant celà pourrait poser problème au sein même du système.
tty_getc peut se permettre d'être bloquante car c'est une fonction en mode utilisateur.

### E8
seg_code a une taille d'environ 1300 instructions.


## F - Exécution du code binaire sur le prototype virtuel

### F1
cycle0: miss cache d'instructions (1cycle)
cycle1: request/gnt (cache -> bus -> ram)
cycle2: pibus  select ROM (rafales)
cycle3: pibus read_dtad
cycle4: read_dtad
cycle5: read_dtad fin de la rafale (derniere addresse)
cycle6: read_data (derniere donnée)
cycle7: icache miss wait
cycle8: icache update (1cycle)
cycle9: IDLE??read_ad
cycle10: InsRsp -> valid no error ins 0x3c1d0200 (première instruction et insère le prochaine octet=la prochaine instruction)
...
cycle14: miss cache d'instructions

La première transaction du bus correspond à un miss du cache d'instructions qui mène à une transaction en rafales d'un mot de 32 bits. Donc octet par octet sur le pibus.
L'échange est du cache d'instruction à la ROM et il demande le premier mot du segment mémoire seg_reset.
La première instruction en mémoire a lieu au cycle 10.
La deuxième transaction du bus correspond à, comme la première, un miss du cache d'instructions qui mène à une transaction en rafales de 4 octets.

### F2
Ctrl+F [sel_ram = 0x1] -> première occurrence
La première instruction s'exécute au cycle 27, car celà provoque un miss du cache de données.

La première instruction s'exécute au cycle 50 car on passe en mode USER:
>proc : <InsReq    valid mode MODE_USER @ 0x4012e8>

### F3
Au cycle 76 on a sel_ram = 0x1 et miss DCACHE_MISS_SELECT,
celà correspond donc à la première transaction correspondant à la lecture de "hello world".

### F4
La première écriture vers le termibnal TTY se trouve au cycle 1176:
PIBUS_WRITE_AD
sel_tty = 0x1
read    = 0