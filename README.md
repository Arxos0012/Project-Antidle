# Project-Antidle
A game that revolves around collect abilities, not items.

This was a project created for my high school Coding Design class. Beneath are instructions for building and running the game yourself:

###Prerequisites
Have Microsoft Windows 7 or later installed as your operating system.

Have the "Microsoft Visual Studios Express 2013 for Windows Desktop" IDE installed (can be found here: https://www.visualstudio.com/downloads/download-visual-studio-vs)

Have SDL downloaded and placed in the correct directory:

1. First download the SDL Development Library for Windows from here (the Visual C++ version): https://www.libsdl.org/download-2.0.php; and download the SDL-image Development Library for Windows library from here (the Visual C++ version): https://www.libsdl.org/projects/SDL_image/
2. Got to your C:/ folder and create folders for both the SDL library and the SDL_image library. You may name them what ever you want, but you must remeber the names of these folders for later. Extract the contents of the both zip files to their respective folders.

###Building and Playing:
1)  Open Visual Studios. In the toolbar got to Team->Connect to Team Foundation Server. The "Team Explorer" tab should pop up.

2)  Under "Local Git Repositories", select Clone and copy the URL to this project in the textfield, then select "Clone".

3)  Now go to C:\Users\(your username)\Source\Repos\Project-Antidle\Debug.

4)  In another File Explorer window got to the SDL folder created in the prerequisite. Go to lib\x86 in the SDL folder and copy
    the SDL2.dll into the the Debug folder. Go to your SDL_image folder, open lib/x86, and copy all .dll files to the Debug
    folder as well.

5)  Go back to Visual Studios. Select View->Solution Explorer in the toolbar. In the "Solution Explorer" tab, on the second
    line, right click "Project Antidle" and select Properties.

6)  In Configueration Properties->C/C++->General, click on field of text next to "Additional Include Directies" and then click
    on the box with a down arrow that pops up at left end of that field. Select "<Edit...>". Double click on the textbox of the
    resulting window and then select the box labeled "..." that pops up. Navigate to and select the directiory of the "include"
    folder in your SDL folder. Repeat this for the "include" folder in you SDL_image folder. Next select the "OK" button at the
    bottom of the window.

7)  Now in Configueration Properties->Linker->General, click on field of text next to "Additional Library Directies" and then
    click on the box with a down arrow that pops up at left end of that field. Select "<Edit...>". Double click on the textbox
    of the resulting window and then select the box labeled "..." that pops up. Navigate to and select the directiory of the
    "lib\x86" folder in your SDL folder. Repeat this for the "lib\x86" folder in you SDL_image folder. Next select the "OK"
    button at the bottom of the window.

8)  Now in Configueration Properties->Linker->Input, click on field of text next to "Additional Dependencies" and then
    click on the box with a down arrow that pops up at left end of that field. Select "<Edit...>". Type "SDL2.lib",
    "SDL2main.lib", and "SDL2_image.lib" each on their own line in the textbox then select "OK".
    
9)  Now in Configueration Properties->Linker->System, click on field of text next to "SubSystem" and select "Console
    (/SUBSYSTEM:CONSOLE)".

10) Click "OK". Go to Build in the toolbar and select "Build Solution". Wait for the project to build, then got to Debug in the
    toolbar and select "Start Debugging". The game should be up and running.

###Controls:

W: move up
S: move down
A: move left
D: move right

Left Click: Use first ability
Right Click: Use second ability

###Gameplay

You will start off in the middle of the map. You must find and locate the abilities on the map to kill the enemies that are stalking you. Though you cannot phase through the walls, they can, so try not to get trapped. Collect ability simply by moving over them. Extermiate the enemies and win the game. Syro Skenict!
