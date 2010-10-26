Welcome to XPwn!
----------------

The X is for "cross", because unlike PwnageTool, this utility has no
dependencies on proprietary, closed-source software and can potentially be
compiled and used on any platform.

This is a special proof-of-concept version available on any platform,
compiled with static libraries to minimize potential issues (which is why the
executables are a bit on the heavy side).

The source is released under the terms of the GNU General Public License
version 3. The full text of the license can be found in the file LICENSE. The
source code itself is available at: http://github.com/planetbeing/xpwn

What XPwn is
------------

A barebones pwnagetool implementation that is easily portable.

What XPwn is *NOT*
------------------

An easy-to-use tool suitable for beginners. While it is possible easy to use
user interfaces will be developed for it eventually, it's mostly meant to be
a toy for *nix geeks. Absolutely no support should be expected or will be
given.


Credits
-------

This utility is implementation of Pwnage, which is the work of
roxfan, Turbo, wizdaz, bgm, and pumpkin. Those guys are the real heroes.

Also, the new super-awesome bootrom exploit is courtesy of wizdaz.

MuscleNerd has put a lot of work into the 3G effort. The BootNeuter unlock
for first-generation iPhones packaged within is primarily his effort.

Thanks also go to gray and c1de0x for their RCE efforts. saurik is the author
of Cydia, included within. bugout was the lucky guy who did our first 3G tests.

Thanks to chris for his hardware wisdom, Zf for his French humor, and pytey
for the support on the serial stuff.

idevice's "ready for custom IPSW" art was graciously contributed by KinetiX

XPwn attempts to use all the same data files and patches as PwnageTool to
avoid duplication of present and future labor. I believe that wizdaz probably
put the most sweat into PwnageTool, and the pwnage ramdisk is the work of
Turbo.

XPwn on Linux would not have been possible without libibooter, which was
written by cmw, based on the Linux iPhone recovery driver written by geohot.

A special shout-out to cmw, who I have been helping with winpwn. He's put a
lot of hard work into winpwn, and should also be credited with doing some of
the initial exploratory work with the undocumented DMG format.

Usage
-----

There are three utilities in this package, as well as the bundles and
FirmwareBundles folders from PwnageTool, and Turbo's autopwn ramdisk.

*NOTE: Img3 decoding has been changed in newer firmwares (>= 3.1). Backwards
compatibility with older firmwares is achieved by passing "--old-img3-decrypt"
to imagetool, ipsw, xpwntool.*

## Overview

The general series of steps should be to use ipsw to create a custom IPSW with
the user's preferences (done once per custom ipsw required), then itunespwn
(done once per computer) so that future DFU restores will be made easier.
Finally, either dfu-util (Mac or Linux) or idevice (Windows) should be used as
necessary on the iPhone to perform the actual exploit necessary to allow it to
accept our code.

It is technically possible to skip itunespwn and just use idevice or skip
idevice and just use itunespwn, but I recommend doing both.

## ipsw

ipsw is a more complex tool to generate custom IPSWs that you can restore
after using xpwn (or any other pwnage-based utility). This is important, since
that's how the jailbreak actually occurs.

	./ipsw <input.ipsw> <output.ipsw> [-b <bootimage.png>] [-nowipe] \
		[-bbupdate] [-s <disk0s1 size>]  [-r <recoveryimage.png>] \
		[-memory] [-e "<action to exclude>"] \
		[[-unlock] [-use39] [-use46] [-cleanup] \
		-3 <bootloader 3.9 file> -4 <bootloader 4.6 file>] \
		<package1.tar> <package2.tar>...


Yes, I know, confusing syntax. The first two options are the IPSW you want to
modify, and where you want to save the modified IPSW respectively. -b and -r
have the same semantics and requirements as for xpwn. You can also specify
actions to exclude from the "FilesystemPatches" section of the Info.plist
for your particular IPSW (in FirmwareBundles/).

The most common use of the '-e' flag is to disable automatic activation, i.e.
'-e "Phone Activation"'. Note that the double-quotes are necessary.

-s allows you to specify the size of the system partition. This value is
specified in megabytes (NOT mebibytes)

-memory allows you to specify that memory instead of temporary files should be
used whenever possible (no longer the default).

-nowipe disables Apple's wiping of the NAND (user data), before proceeding
with the restore. This allows the restore to happen much, much more quickly.

-bbupdate tells the restore ramdisk to attempt to upgrade your baseband. This
is disabled by default for unlock safety reasons.

-unlock, -use39, -use46, -cleanup, -3, and -4 are valid only if you merge the
BootNeuter package. These provide instructions to BootNeuter (which provides
unlocking for iPhones). If you choose to use BootNeuter, you must specify the
location where the 3.9 and 4.9 bootloader can be found with the -3 and -4
options. These cannot be included with xpwn due to copyright restrictions.

-unlock specifies that you wish BootNeuter to unlock the phone (if it is not
already unlocked). -use39 and -use46 instructs BootNeuter to either upgrade
or downgrade your bootloader (if it is not already on the version you choose).
-cleanup instructs BootNeuter to delete itself off of the iPhone after it is
complete. If you do not specify -cleanup, BootNeuter will be accessible via
SpringBoard.

The last options are for tar-files to merge. All permissions and ownership
will be preserved except for already directories that already exist. This is
to prevent accidental clobbering (we're guessing you don't really want to
alter permissions on existing directories). This behavior may change in the
future.

Told you it was a mess.

### Examples

Jailbreaking iPod 2.0:

	./ipsw iPod1,1_2.0_5A347.ipsw custom.ipsw \
		bundles/Cydia.tar

Jailbreaking iPhone 3G:

	./ipsw iPhone1,2_2.0_5A347.ipsw custom.ipsw \
		-e "Phone Activation" bundles/Cydia.tar

Jailbreaking, activating, and unlocking iPhone 2.0:

	./ipsw iPhone1,1_2.0_5A347.ipsw custom.ipsw \
		-unlock -cleanup -3 bl39.bin -4 bl46.bin \
		bundles/Cydia.tar \
		bundles/BootNeuter.tar \
		bundles/YoutubeActivation.tar

Technical notes
---------------

The ipsw tool loads the entire contents of the IPSW into memory before
manipulating it. This is especially useful, because it allows all the
necessary transformations to be done without writing the intermediate steps to
disk and slowing the process down. ipsw is hence even faster than the Mac
pwnagetool.

However, hefty virtual memory requirements are necessary: 500 MB for the ipsw 
tool. Most modern computers should have that much to spare. Not all
of it needs to be free physical, as memory is accessed in a sequential manner
so thrashing should be kept to a minimum. In the worst case, it should be
equivalent to just writing intermediate results to disk. In essence, virtual
memory is used as an intelligent cache.

On the other hand, this also means that devices such as the iPhone itself
cannot run these utilities without modification. The necessary modifications
are actually relatively simple. Instead of using an AbstractFile backed by
memory, an AbstractFile backed by a physical file can be used again. Contact
me if this functionality is desired.

## Libraries used

- bsdiff
- libibooter
- libbzip2
- libcrypto (from OpenSSL)
- libpng
- libusb
- libz

These are all statically compiled in, but it should give you a good idea of
the program's dependencies.

Linux Notes:
------------
Question: Is there a way to restore the iPhone from Linux?

Answer: There is posixninja's "idevicerestore", but it currently isn't in a fully
usable state. You can check it out, though.

