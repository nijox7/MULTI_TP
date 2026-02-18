# Compte-rendu TP1

## Automates et fonctions de génération

!["Page1"](img/automate1.png)
!["Page2"](img/automate2.png)

## E. Automate du composant PibusSegBcu

### E3
L'arbitre choisit un maître dans l'état IDLE et dans l'état DT dans le cas où si un autre maître demande l'accès au bus. Le nouveau maître pourra donc demander lorsque le BCU est dans l'état DT puisque l'ancien maître se sera déconnecté dans cet état.

## F. Modélisation de l'architecture matérielle

### F1.
Voici les lignes de codes rajoutées/complétées:

PibusSimpleMaster master("master", SEG_RAM_BASE, SEG_TTY_BASE);
PibusSimpleRam    ram("ram", 1, segtable, ram_latency, loader);

master.p_ck		(signal_ck);
master.p_resetn	(signal_resetn);
master.p_gnt	(signal_gnt_master);
master.p_req	(signal_req_master)
master.p_a		(signal_pi_a);
master.p_opc	(signal_pi_opc);
master.p_read	(signal_pi_read);
master.p_lock	(signal_pi_lock);
master.p_d		(signal_pi_d);
master.p_ack	(signal_pi_ack);
master.p_tout	(signal_pi_tout);
	
ram.p_ck		(signal_ck);
ram.p_resetn	(signal_resetn);
ram.p_sel		(signal_sel_ram);
ram.p_a			(signal_pi_a);
ram.p_read		(signal_pi_read);
ram.p_opc		(signal_pi_opc);
ram.p_ack		(signal_pi_ack);
ram.p_d			(signal_pi_d);
ram.p_tout		(signal_pi_tout);

### F2.
segtable.addSegment("seg_tty", SEG_TTY_BASE, 0X00000010, 1, false);

### F3.


## G. Simulation

### G1
On mesure un temps de simulation d'environ 8 secondes.
On a donc 10 000 000 / 8 = 1 250 000 cycles par secondes.
Voici la trace de l'exécution:

[carbou@machaut test]$ ./simul.x -NCYCLES 10000000
 ____            _                  ____    _    ____ ____  
/ ___| _   _ ___| |_ ___ _ __ ___  / ___|  / \  / ___/ ___| 
\___ \| | | / __| __/ _ \ '_ ` _ \| |     / _ \ \___ \___ \ 
 ___) | |_| \__ \ ||  __/ | | | | | |___ / ___ \ ___) |__) |
|____/ \__, |___/\__\___|_| |_| |_|\____/_/   \_\____/____/ 
       |___/                                                

         Cycle Accurate System Simulator
            ASIM/LIP6/UPMC
            E-mail support:  Richard.Buchmann@asim.lip6.fr
            Contributors : Richard Buchmann, Sami Taktak,
                           Paul-Jerome Kingbo, Frederic P�trot,
                           Nicolas Pouillon

                           Last change : Oct 22 2019


********************************************************
******        tp1_multi                           ******
********************************************************

Trying to load a plain blob from file 'string_file' @ 0x10000000 flags: D
Loading a plain blob from file 'string_file' @ 10000000, size: 14 bytes,  flags: 3

Instanciation of PibuBcu : bcu
    nb_master = 1
    nb_target = 2
    time_out  = 100

Instanciation of PibusSimpleMaster : master
    tty base address = 0xc0000000
    ram base address = 0x10000000

Instanciation of PibusSimpleRam : ram
    latency = 2
    segment seg_ram | base = 0x10000000 | size = 0x10

Instanciation of PibusMultiTty : tty
    ntty = 1
    segment seg_tty | base = 0xc0000000 | size = 0x10

Loading at 0x10000000 size 0x10: string_file 
[carbou@machaut test]$ 




Pour obtenir une trace de l'exécution on tape cette commande:

./simul.x -NCYCLES 10000 -TRACE 0 > trace

Le résultat se trouve dans le fichier trace.save.

### G2
Il n'y en a pas car c'est le seul composant à demander l'accès au bus.

### G3
Il y a 2 cycles d'attente dans l'automate du maître lorsqu'il attend la réponse de la RAM.
Cela est du à la latence de réponse de la ram (2 cycles par défaut dans ce simulateur).

### G4
Pour afficher un caractère sur le composant PIBUS_MULTI_TTY il faut 3 cycles à l'automate du maître.

### G5
Voici le chronogramme que j'ai réalisé sans utilisé le fichier trace:
!["Chronogramme sans le fichier trace"](img/chronogramme.png)

Voici le chronogramme final fait avec le fichier trace:
!["Chronogramme avec le fichier trace"](img/chronogramme_trace.png)
