# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.Assignment04.Debug:
/Users/TJC/Desktop/SUNYPOLY/CS450/CS_450_548_Assign04_Files/Debug/Assignment04:\
	/usr/local/lib/libGLEW.dylib
	/bin/rm -f /Users/TJC/Desktop/SUNYPOLY/CS450/CS_450_548_Assign04_Files/Debug/Assignment04


PostBuild.Assignment04.Release:
/Users/TJC/Desktop/SUNYPOLY/CS450/CS_450_548_Assign04_Files/Release/Assignment04:\
	/usr/local/lib/libGLEW.dylib
	/bin/rm -f /Users/TJC/Desktop/SUNYPOLY/CS450/CS_450_548_Assign04_Files/Release/Assignment04


PostBuild.Assignment04.MinSizeRel:
/Users/TJC/Desktop/SUNYPOLY/CS450/CS_450_548_Assign04_Files/MinSizeRel/Assignment04:\
	/usr/local/lib/libGLEW.dylib
	/bin/rm -f /Users/TJC/Desktop/SUNYPOLY/CS450/CS_450_548_Assign04_Files/MinSizeRel/Assignment04


PostBuild.Assignment04.RelWithDebInfo:
/Users/TJC/Desktop/SUNYPOLY/CS450/CS_450_548_Assign04_Files/RelWithDebInfo/Assignment04:\
	/usr/local/lib/libGLEW.dylib
	/bin/rm -f /Users/TJC/Desktop/SUNYPOLY/CS450/CS_450_548_Assign04_Files/RelWithDebInfo/Assignment04




# For each target create a dummy ruleso the target does not have to exist
/usr/local/lib/libGLEW.dylib:
