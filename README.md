# CG1111_Project


How to use:
1. Download the source from the git https://codeload.github.com/Makeblock-official/Makeblock-Libraries/zip/master

2. In the Arduino IDE: "Sketch-> Include Library-> Add .ZIP Library-> select the downloaded file-> Open"

3. Click "File-> Examples". There are some test programs in "MakeBlockDrive->"

4. Depending on the type of board you're using, you need to modify the header file to match.

For example, if you're using a mCore. You should change #include <MeOrion.h> to #include <MeMCore.h> Corresponding boards and there header file are:

Orion <--------> MeOrion.h

BaseBoard <----> MeBaseBoard.h

mCore <--------> MeMCore.h

Shield <-------> MeShield.h

Auriga <-------> MeAuriga.h

MegaPi <-------> MeMegaPi.h
