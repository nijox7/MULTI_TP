GIET_SYS_PATH=/users/enseig/alain/giet_2011/sys
GIET_APP_PATH=/users/enseig/alain/giet_2011/app
MIP=mipsel-unknown-elf-

all: sys.bin app.bin

# SYS
sys.bin: reset.o giet.o drivers.o common.o ctx_handler.o irq_handler.o sys_handler.o exc_handler.o
	$(MIP)ld -o sys.bin -T sys.ld reset.o giet.o drivers.o common.o ctx_handler.o irq_handler.o sys_handler.o exc_handler.o
	$(MIP)objdump -D sys.bin > sys.bin.txt

reset.o: reset.s
	$(MIP)as -g -mips32 -o reset.o reset.s

giet.o: $(GIET_SYS_PATH)/giet.s
	$(MIP)as -g -mips32 -o giet.o $(GIET_SYS_PATH)/giet.s

drivers.o: $(GIET_SYS_PATH)/drivers.c
	$(MIP)gcc -Wall -mno-gpopt -ffreestanding -mips32 -I$(GIET_SYS_PATH) -I. -c -o drivers.o $(GIET_SYS_PATH)/drivers.c

common.o: $(GIET_SYS_PATH)/common.c
	$(MIP)gcc -Wall -mno-gpopt -ffreestanding -mips32 -I$(GIET_SYS_PATH) -I. -c -o common.o $(GIET_SYS_PATH)/common.c

ctx_handler.o: $(GIET_SYS_PATH)/ctx_handler.c
	$(MIP)gcc -Wall -mno-gpopt -ffreestanding -mips32 -I$(GIET_SYS_PATH) -I. -c -o ctx_handler.o $(GIET_SYS_PATH)/ctx_handler.c

irq_handler.o: $(GIET_SYS_PATH)/irq_handler.c
	$(MIP)gcc -Wall -mno-gpopt -ffreestanding -mips32 -I$(GIET_SYS_PATH) -I. -c -o irq_handler.o $(GIET_SYS_PATH)/irq_handler.c

sys_handler.o: $(GIET_SYS_PATH)/sys_handler.c
	$(MIP)gcc -Wall -mno-gpopt -ffreestanding -mips32 -I$(GIET_SYS_PATH) -I. -c -o sys_handler.o $(GIET_SYS_PATH)/sys_handler.c

exc_handler.o: $(GIET_SYS_PATH)/exc_handler.c
	$(MIP)gcc -Wall -mno-gpopt -ffreestanding -mips32 -I$(GIET_SYS_PATH) -I. -c -o exc_handler.o $(GIET_SYS_PATH)/exc_handler.c

# APP
app.bin: stdio.o main.o
	$(MIP)ld -o app.bin -T app.ld stdio.o main.o
	$(MIP)objdump -D app.bin > app.bin.txt

stdio.o: $(GIET_APP_PATH)/stdio.c
	$(MIP)gcc -Wall -mno-gpopt -ffreestanding -mips32 -I$(GIET_APP_PATH) -I. -c -o stdio.o $(GIET_APP_PATH)/stdio.c

main.o: main.c
	$(MIP)gcc -Wall -mno-gpopt -ffreestanding -mips32 -I$(GIET_APP_PATH) -I. -c -o main.o main.c

clean:
	rm -f *.o