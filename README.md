# Uncheater Bypass

Uncheater is a home-rolled anti-cheat made by WEMADE and used in their Unreal Engine games such as MIR4. At first glance it appears to be some crooked/lite version of XIGNCODE3, but essentially it's just a bunch of WINAPI calls (with server auth.), and leads to a ton of false positives/bans. You may be banned for having certain processes open in the background but not in any way related to their game, resulting in a ton of time and effort wasted playing.  

This works as a 'proxy dll' in the sense that it replaces a real file and then calls functions from the real DLL, while the game loads yours and thinks yous is real. The correct exports are needed (found in the .def file) or the entire process will fail.
