## SPDX-License-Identifier: GPL-2.0-only

CPPFLAGS_common += -I$(src)/mainboard/$(MAINBOARDDIR)/include
subdirs-y += variants/$(VARIANT_DIR)

bootblock-y += bootblock.c

ramstage-y += devtree.c
ramstage-y += hda_verb.c
ramstage-y += mainboard.c
ramstage-y += smbios.c
ramstage-$(CONFIG_MAINBOARD_USE_LIBGFXINIT) += gma-mainboard.ads
