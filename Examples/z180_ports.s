;***********************************************************
;* original File name: 185macro.lib                        *
;* Macro library for Z180 Memory-Mapped Registers          *
;*                                                         *
;*                     1/26/89 Jim Nobugaki                *
;*         revised     7/14/92 Del Miranda                 *
;*    80185            Sept.94 Craig MacKenna              *
;* Modified for ZMASM  8/11/97 Quyen Tran                  *
;* modified for zasm   2017-09-30 Kio                      *
;***********************************************************

; Z180 System Control Registers

; ASCI Registers
cntla0:	equ	00h	; ASCI Cont Reg A Ch0
cntla1:	equ	01h	; ASCI Cont Reg A Ch1
cntlb0:	equ	02h	; ASCI Cont Reg B Ch0
cntlb1:	equ	03h	; ASCI Cont Reg B Ch1
stat0:	equ	04h	; ASCI Stat Reg Ch0
stat1:	equ	05h	; ASCI Stat Reg Ch1
tdr0:	equ	06h	; ASCI Tx Data Reg Ch0
tdr1:	equ	07h	; ASCI Tx Data Reg Ch1
rdr0:	equ	08h	; ASCI Rx Data Reg Ch0
rdr1:	equ	09h	; ASCI Rx Data Reg Ch1
tsr0:	equ	08h	; ASCI Tx Data Reg Ch0
tsr1:	equ	09h	; ASCI Tx Data Reg Ch1
asext0:	equ	12h	; asci0 extension control reg
asext1:	equ	13h	; asci1 extension control reg
astc0l:	equ	1ah	; asci0 time constant low
astc0h:	equ	1bh	; asci0 time constant high
astc1l:	equ	1ch	; asci1 time constant low
astc1h:	equ	1dh	; asci1 time constant high

; Timer Registers
tmdr0l:	equ	0ch	; Timer Data Reg Ch0-low
tmdr0h:	equ	0dh	; Timer Data Reg Ch0-high
rldr0l:	equ	0eh	; Timer Reload Reg Ch0-low
rldr0h:	equ	0fh	; Timer Reload Reg Ch0-high
tcr:	equ	10h	; Timer Cont Reg
tmdr1l:	equ	14h	; Timer Data reg Ch1-low
tmdr1h:	equ	15h	; Timer Data Reg Ch1-high
rldr1l:	equ	16h	; Timer Reload Reg Ch1-low
rldr1h:	equ	17h	; Timer Reload Reg Ch1-high
frc:	equ	18h	; Free Running Counter

; CPU Control Registers
ccr:	equ	1fh	; CPU Control Reg.

;DMA Registers
sar0l:	equ	20h	; DMA Source Addr Reg Ch0-low
sar0h:	equ	21h	; DMA Source Addr Reg Ch0-high
sar0b:	equ	22h	; DMA Source Addr Reg Ch0-b
dar0l:	equ	23h	; DMA Dist Addr Reg Ch0-low
dar0h:	equ	24h	; DMA Dist Addr Reg Ch0-high
dar0b:	equ	25h	; DMA Dist Addr Reg Ch0-B
bcr0l:	equ	26h	; DMA Byte Count Reg Ch0-low
bcr0h:	equ	27h	; DMA Byte Count Reg Ch0-high
mar1l:	equ	28h	; DMA Memory Addr Reg Ch1-low
mar1h:	equ	29h	; DMA Memory Addr Reg Ch1-high
mar1b:	equ	2ah	; DMA Memory Addr Reg Ch1-b
iar1l:	equ	2bh	; DMA I/O Addr Reg Ch1-low
iar1h:	equ	2ch	; DMA I/O Addr Reg Ch1-high
iar1b:	equ	2dh	; DMA new in 185
bcr1l:	equ	2eh	; DMA Byte Count Reg Ch1-low
bcr1h:	equ	2fh	; DMA Byte Count Reg Ch1-high
dstat:	equ	30h	; DMA Stat Reg
dmode:	equ	31h	; DMA Mode Reg
dcntl:	equ	32h	; DMA/WAIT Control Reg

;System Control Registers
il:	equ	33h	; INT Vector Low Reg
itc:	equ	34h	; INT/TRAP Cont Reg
rcr:	equ	36h	; Refresh Cont Reg
cbr:	equ	38h	; MMU Common Base Reg
bbr:	equ	39h	; MMU Bank Base Reg
cbar:	equ	3ah	; MMU Common/Bank Area Reg
omcr:	equ	3eh	; Operation Mode Control Reg
icr:	equ	3fh	; I/O Control Reg

; 80185 registers
wsgcs:  equ	0d8h	; wait state/CS reg
p1ctc:  equ	0deh	; PIA1/CTC pin select reg
intedge:equ	0dfh	; Interrupt edge register
rombr:  equ	0ech	; rom upper boundary
ramlbr: equ	0ebh	; ram lower boundary
ramubr: equ	0eah	; ram upper boundary
syscr:  equ	0edh	; system pin control

;SCC Registers
scc_d:	equ	0e9h	;addr of scc - data
scc_c:	equ	0e8h	;addr of scc - cont

;PIO registers
ddr1:	equ	0e0h	; data direction, port 1 
ddr2:	equ	0e2h	; data direction, port 2
dr1: 	equ	0e1h	; port 1 data
dr2: 	equ	0e3h	; port 2 data

; CTC registers
ctc0:	equ	0e4h
ctc1:	equ	0e5h
ctc2:	equ	0e6h
ctc3:	equ	0e7h

; watchdog timer registers
wdtmr:	equ	0f0h
wdtcr:	equ	0f1h

; bidirectional centronics registers
parm:   equ	0d9h	
parc:   equ	0dah	; like a green place
parc2:  equ	0dbh	
part:   equ	0dch	; read as "party"
parv:   equ	0ddh	; in memory of dr. gupta
altdr2: equ	0eeh	; alternate address for port 2 data
