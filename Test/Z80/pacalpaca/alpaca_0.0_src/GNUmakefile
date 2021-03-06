# GNUMakefile for the Alpaca project
#
#    Scott "Jerry" Lawrence
#  
#  It's not pretty.  Sorry about that...
#  

#
# $Id: GNUmakefile,v 1.53 2003/08/22 19:29:33 jerry Exp $
#

############################################################
# Targets:
#	paclisting	builds: code/pacalpaca.lst listing file
#	pacprog		builds: code/pacalpaca.asm, code/pacfinal.ihx
#	pacroms		builds: roms/pacman/pacman.* (graphics and code)
#	pacromzip	builds a zip of the above roms
#	pactest		builds the pac-man roms, runs MAME to test them out
#
#	pengolisting	builds: code/pacalpaca.lst listing file
#	pengoprog	builds: code/pacalpaca.asm, code/pacfinal.ihx
#	pengoroms	builds: roms/pengo/pengo.* (graphics and code)
#	pengoromzip	builds a zip of the above roms
#	pengotest	builds the pengo roms, runs MAME to test them out
#
#	docs		builds: doc/alpaca.pdf
#	dview		builds: doc/alpaca.pdf, runs acroread
#
#	clean		gets rid of all targets
#	tidy		cleans the doc directory of intermediate files
#
#	dist		web-ready distribution
#	backup		source distribution (everything)
#
#	all		builds: docs, roms, listing

############################################################
all: docs paclisting pengolisting pacroms pengoroms
############################################################
test: paclisting pactest
############################################################

HAS_NOWEB := 1

############################################################

# program name
PROG    := alpaca
VERSION := 0.8

# extra programs
GENROMS  := genroms
TURACOCL := turacocl
DD       := dd
ZIP      := zip
TAR	 := tar --exclude=CVS --exclude=.*
BLDSYS   := $(shell uname -s)

# directories
CODEDIR   := code
ROMSROOT  := roms
ROMSOURCE := roms/dummy
DISTDIR   := $(PROG)_$(VERSION)

# backup files
THISDIR   := alpaca
TARFILE   := $(PROG)_$(VERSION)_src.tar


#########################################
# emulator selection
#   - for testing romsets

# if we want to use xmame on OS X, set EMULATOR to ForceXMame
EMULATOR := ForceXMame


# the name of the xmame executable
XMAME    := xmame 

# the name of the xmame executable with the debugger compiled in
XMAMED   := xmamed -debug

# parameters for all Xmame versions:
MAMEPARAMS := -skip_disclaimer -skip_gameinfo

# and the xmame to use.  (set XMAMED to XMAME for no debugger)
XMAMEUSE := $(XMAME) $(MAMEPARAMS)


# apps and dirs for OS X testing of Pac-Man

# osx app to use to test Pac roms
PMTAPP := /Applications/jerry/Games/MacPacMAME\ 0.58ƒ/MacPacMAME\ 0.58
# dir to copy pac roms into
PMTRD  := /Applications/jerry/Games/MacPacMAME\ 0.58ƒ/ROMS/pengman

# apps and dirs for OS X testing of Pengo

# osx app to use to test Pengo roms
PGTAPP := /Applications/jerry/Games/MacMAME/MacMAME.app
# dir to copy pengo roms into
PGTRD  := /Applications/jerry/Games/MacMAME/ROMs/pengo2u


########################################

ifdef HAS_NOWEB

NWS := \
	nws/title.nw \
	nws/overview.nw \
	nws/arch.nw \
	nws/init.nw \
	nws/kernserv.nw \
	nws/semaphores.nw \
	nws/messages.nw \
	nws/malloc.nw \
	nws/isr.nw \
	nws/coretask.nw \
	nws/exec.nw \
	nws/task0.nw \
	nws/task1.nw \
	nws/task2.nw \
	nws/task3.nw \
	nws/utils.nw \
	nws/error.nw \
	\
	nws/appendix.nw \
	nws/schedule.nw \
	nws/hardware.nw \
	nws/asm.nw \
	nws/auxdata.nw \
	nws/build.nw \
	nws/license.nw \
	nws/end.nw

PCX :=\
	gfx/pacscreen.pcx \
	gfx/pac_1.pcx \
	gfx/pac_1c.pcx \
	gfx/pac_2.pcx \
	gfx/pac_2c.pcx 

PCXPDF := $(PCX:%.pcx=%.pdf)

endif

STYLE := doc/alpaca.sty
DOC := doc/$(PROG).pdf

docs:	$(DOC) 

dview:	docs
	open $(DOC)

############################################################

PACTARG := $(CODEDIR)/pacfinal.ihx
PACASMS := $(CODEDIR)/pacalpaca.asm

PENGOTARG := $(CODEDIR)/pengofinal.ihx
PENGOASMS := $(CODEDIR)/pengoalpaca.asm

DEPS := 

DATA :=

CLEAN := Release Build $(DISTDIR)

ifdef HAS_NOWEB
    CLEAN += $(PENGOTARG) $(PENGOTARG:%.ihx=%.map) 
    CLEAN += $(PENGOASMS) $(PENGOASMS:%.asm=%.rel)
    CLEAN += $(PACTARG) $(PACTARG:%.ihx=%.map) 
    CLEAN += $(PACASMS) $(PACASMS:%.asm=%.rel)
    CLEAN += doc/alpaca* code/*.lst
    CLEAN += roms/pacman/pacman.* pac*.zip
    CLEAN += roms/pengo2u/pengo*.* pengo*.zip
    CLEAN += roms/pengo2u/ic*
endif

TIDY := $(COMMON_OBJS) $(STYLE) \
	$(DOC:%.pdf=%.tex) $(DOC:%.pdf=%.aux) \
	$(DOC:%.pdf=%.log) $(DOC:%.pdf=%.toc) \
	$(PCXPDF) $(DOC:%.pdf=%.out) 



############################################################
# Pac builds

# various config
PACROMDIR      := $(ROMSROOT)/pacman
PACBACKDIR     := ../..
PACGENROMSFILE := $(CODEDIR)/pacman.roms
PACTURACOINI   := $(CODEDIR)/pacman.ini
PACROMNAME     := pacman

CLEAN += $(PACGENROMSFILE) 
CLEAN += $(PACTURACOINI)


pacprog:	$(PACTARG)
.PHONY: pacprog

pacroms:	$(PACTARG) $(PACGENROMSFILE) $(PACTURACOINI)
	cd $(PACROMDIR) ;\
		$(GENROMS) $(PACBACKDIR)/$(PACGENROMSFILE)\
			   $(PACBACKDIR)/$(PACTARG)
	$(DD) if=/dev/zero of=$(PACROMDIR)/pacman.5e bs=4096 count=1
	$(DD) if=/dev/zero of=$(PACROMDIR)/pacman.5f bs=4096 count=1
	$(TURACOCL) -inf IMG -bnk 1 -rod $(PACROMDIR)\
		    -rom $(PACROMDIR) -ini $(PACTURACOINI)\
		    -dbf gfx/pac_1.pcx
	$(TURACOCL) -inf IMG -bnk 2 -rod $(PACROMDIR)\
		    -rom $(PACROMDIR) -ini $(PACTURACOINI)\
		    -dbf gfx/pac_2.pcx
.PHONY: pacroms 

pacromzip:	pacroms
	mkdir $(PACROMNAME)
	cp $(PACROMDIR)/8* $(PACROMDIR)/p* $(PACROMNAME)
	$(ZIP) -r $(PACROMNAME).zip $(PACROMNAME)
	rm -rf $(PACROMNAME)
.PHONY: pacromzip


########################################
# PAC test targets

# automagically choose the correct one..
ifeq ($(BLDSYS),Darwin)
 ifeq ($(EMULATOR),ForceXMame)
pactest:	pacroms mamepactest
 else
pactest:	pacroms osxpactest
 endif
else
pactest:	pacroms mamepactest
endif
.PHONY: pactest


osxpactest:
	cp -f $(PACROMDIR)/pacman.* $(PMTRD)
	cp -f $(PACROMDIR)/82*.* $(PMTRD)
	open -a $(PMTAPP)
.PHONY: osxpactest


mamepactest:
	$(XMAMEUSE) -rp $(ROMSROOT) pacman
.PHONY: mamepactest



############################################################
# Pengo builds

# various config
PENGOROMDIR      := $(ROMSROOT)/pengo2u
PENGOBACKDIR     := ../..
PENGOGENROMSFILE := $(CODEDIR)/pengo2u.roms
PENGOTURACOINI   := $(CODEDIR)/pengo2u.ini
PENGOROMNAME     := pengo2u

CLEAN += $(PENGOGENROMSFILE) 
CLEAN += $(PENGOTURACOINI)


pengoprog:	$(PENGOTARG)
.PHONY: pengoprog

pengoroms:	$(PENGOTARG) $(PENGOGENROMSFILE) $(PENGOTURACOINI)
	cd $(PENGOROMDIR) ;\
		$(GENROMS) $(PENGOBACKDIR)/$(PENGOGENROMSFILE)\
		$(PENGOBACKDIR)/$(PENGOTARG)
	$(DD) if=/dev/zero of=$(PENGOROMDIR)/ic92 bs=8192 count=1
	$(DD) if=/dev/zero of=$(PENGOROMDIR)/ic105 bs=8192 count=1
	$(TURACOCL) -inf IMG -bnk 1 -rod $(PENGOROMDIR)\
		    -rom $(PENGOROMDIR) -ini $(PENGOTURACOINI)\
		    -dbf gfx/pen_1.pcx
	$(TURACOCL) -inf IMG -bnk 2 -rod $(PENGOROMDIR)\
		    -rom $(PENGOROMDIR) -ini $(PENGOTURACOINI)\
		    -dbf gfx/pen_2.pcx
	$(TURACOCL) -inf IMG -bnk 3 -rod $(PENGOROMDIR)\
		    -rom $(PENGOROMDIR) -ini $(PENGOTURACOINI)\
		    -dbf gfx/pen_3.pcx
	$(TURACOCL) -inf IMG -bnk 4 -rod $(PENGOROMDIR)\
		    -rom $(PENGOROMDIR) -ini $(PENGOTURACOINI)\
		    -dbf gfx/pen_4.pcx
.PHONY: pengoroms

pengoromzip:	pengoroms
	mkdir $(PENGOROMNAME)
	cp $(PENGOROMDIR)/ic* $(PENGOROMDIR)/p* $(PENGOROMNAME)
	$(ZIP) -r $(PENGOROMNAME).zip $(PENGOROMNAME)
	rm -rf $(PENGOROMNAME)
.PHONY: pengoromzip


########################################
# PENGO test targets

# automagically choose the correct one..
ifeq ($(BLDSYS),Darwin)
 ifeq ($(EMULATOR),ForceXMame)
pengotest:	pengoroms mamepengotest
 else
pengotest:	pengoroms osxpengotest
 endif
else
pengotest:	pengoroms mamepengotest
endif
.PHONY: pengotest

osxpengotest: 
	cp -f $(PENGOROMDIR)/pengo.* $(PGTRD)
	cp -f $(PENGOROMDIR)/ic* $(PGTRD)
	cp -f $(PENGOROMDIR)/pr163*.* $(PGTRD)
	open -a $(PGTAPP)
.PHONY: osxpengotest


mamepengotest:
	$(XMAMEUSE) -rp $(ROMSROOT) pengo2u
.PHONY: mamepengotest


############################################################

clean:	tidy
	rm -rf $(CLEAN)

tidy:
	rm -rf $(TIDY)

dist: docs paclisting pacromzip pengolisting pengoromzip
	rm -rf $(DISTDIR)
	mkdir $(DISTDIR)
	cp $(DOC) $(DISTDIR)
	cp $(PACLSTS) $(PACASMS) $(DISTDIR)
	cp $(PACROMNAME).zip $(DISTDIR)
	cp $(PENGOLSTS) $(PENGOASMS) $(DISTDIR)
	cp $(PENGOROMNAME).zip $(DISTDIR)

ifeq ($(BLDSYS),Darwin)
backup:	clean
	cd ..; $(TAR) -cvf $(TARFILE) $(THISDIR)
	gzip -f ../$(TARFILE)
else
backup:
	# Sorry, this target is only available under OS X.
endif
.PHONY: backup


############################################################


PACRELS		:= $(PACASMS:%.asm=%.rel)
PACLSTS		:= $(PACASMS:%.asm=%.lst)

PENGORELS	:= $(PENGOASMS:%.asm=%.rel)
PENGOLSTS	:= $(PENGOASMS:%.asm=%.lst)

paclisting:	$(PACLSTS)
pengolisting:	$(PENGOLSTS)

%.lst: %.asm
	asz80 -l $<
.SECONDARY: $(PACASMS) $(PENGOASMS)

OPTS    := -O

$(PACTARG): $(PACRELS)
	aslink -i -m -o $(PACTARG) -b_CODE=0x0000 $(PACRELS)

$(PENGOTARG): $(PENGORELS)
	aslink -i -m -o $(PENGOTARG) -b_CODE=0x0000 $(PENGORELS)

%.rel: %.asm
	asz80 $<

%.rel: %.c
	zcc -c -v $(OPTS) -D$(ARCH) -D$(TEST) -I../include $(ADDS) $<

.SECONDARY: $(PACTARG)
.SECONDARY: $(PENGOTARG)

############################################################

ifdef HAS_NOWEB

$(CODEDIR)/%.asm:	$(NWS)
	-@$(MKDIR_CMD)
	notangle -R$*.asm $^ | cpif $@

$(CODEDIR)/%.roms: 	$(NWS)
	-@$(MKDIR_CMD)
	notangle -R$*.roms $^ | cpif $@

$(CODEDIR)/%.ini: 	$(NWS)
	-@$(MKDIR_CMD)
	notangle -R$*.ini $^ | cpif $@


%.pdf:	%.tex
	-@$(MKDIR_CMD)
	( \
	    cd $(@D); \
	    oldFingerprint="ZZZ" ; \
	    if [ -f $*.aux ]; then \
		fingerprint="`sum $*.aux`" ; \
	    else \
		fingerprint="YYY" ; \
	    fi ; \
	    while [ ! "$${oldFingerprint}" = "$${fingerprint}" ]; do \
		oldFingerprint="$${fingerprint}" ; \
		pdflatex $(<F) ; \
		fingerprint="`sum $(*F).aux`" ; \
	    done ; \
	)

$(DOC:%.pdf=%.tex):	$(PCXPDF) $(NWS)
	-@$(MKDIR_CMD)
	cat $(NWS) | noweave -delay -index | cpif $@

doc/%.sty: nws/%.sty
	-@$(MKDIR_CMD)
	cp $< $@


%.pdf: %.pcx
	convert $< $@

endif

############################################################

.PHONY: all
.PHONY: docs
.PHONY: clean
.PHONY: tidy

#.SECONDARY: $(TIDY)

############################################################

$(DOC): $(PCXPDF) $(STYLE)

############################################################
