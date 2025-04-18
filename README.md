# coreboot for Macbook Pro 8,2 - 8,3
I've implemented `macbookpro-8_2` and `macbookpro-8_3` support for coreboot, forked off of 01 Mar. 2022 coreboot head w/ 8,1 PR of the time.

This **may** need tweaking to work with Macbooks that still have functional dGPUs, but all my boards have been disabled using [`GMUX_gmux.jed`](https://github.com/paranoidnela/macbookpro8-2-resources/blob/main/GMUX_gmux.rar).

# Notes
I've posted more information and resources on these machines over on [a dedicated Macbook Pro 8,2 resources repository](https://github.com/paranoidnela/macbookpro8-2-resources)

Relevant files for this support are in `src/mainboard/apple/macbookpro8_1`.

This repository is based of a dump from an old drive. It is not a recent fork, and is from the middle of development, while it does boot, it may not have EFI support. My first bootable build were branced off the Macbook Air 4,2 tree, but once the 8,1 PR became a viable base, I ported over my 8,2/8,3 fixes.

While this tree might not be needed anymore due to the 8,1 PR, I did want to post my work to preserve, if there is anything valuable.

Note that there might be interesting information in [the blob research in other repository](https://github.com/paranoidnela/macbookpro8-2-resources/tree/main/blobs).
  
# Credits  
The coreboot team and especially Evgeny Zinoviev for their work, without whom this would not have been possible.

# TODO
- properly branch off to different config, this work is based off of Evgeny Zinoviev's efforts on the macbook air 4,2 and macbook pro 8,1 as such it uses the macbookpro8_1 mainboard that they created and I just patched the PR to work with the boards in the bigger machines.
- document what works and what doesn't, even I don't remember nor do I remember what were all the steps involved, I know that one of the hardest things to overcome was the iGPU support because it works quite differently than the 13 inch variant of the laptop
- update this tree to modern coreboot, merge enhancements coming from the 8,1 PR and turn it into a mergeable commit
