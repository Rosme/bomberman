<pre>
 ____                        __                                                    
/\  _`\                     /\ \                                                   
\ \ \L\ \    ___     ___ ___\ \ \____     __   _ __    ___ ___      __      ___    
 \ \  _ <'  / __`\ /' __` __`\ \ '__`\  /'__`\/\`'__\/' __` __`\  /'__`\  /' _ `\  
  \ \ \L\ \/\ \L\ \/\ \/\ \/\ \ \ \L\ \/\  __/\ \ \/ /\ \/\ \/\ \/\ \L\.\_/\ \/\ \ 
   \ \____/\ \____/\ \_\ \_\ \_\ \_,__/\ \____\\ \_\ \ \_\ \_\ \_\ \__/.\_\ \_\ \_\
    \/___/  \/___/  \/_/\/_/\/_/\/___/  \/____/ \/_/  \/_/\/_/\/_/\/__/\/_/\/_/\/_/
</pre>

by Jean-Sébastien Fauteux

I made this project back in the Winter of 2013 as a final project for school.

To understand the context behind the code:
* I was in the process of understanding C++11
* I was still learning about C++ in general
* I was stuck with Visual Studio 2010
* I had just begun learning about design patterns(such as a Factory)
* I had close to no experience in video games development
* This was done with SFML 2.0 RC

Now that is said, you may enjoy(or not) the code behind this bomberman recreation.

Features:
* 3 AI(Aggressive, Defensive, Random)
* Map Editor
* Profile Creation(with custom key mapping)

Known Bugs:
* If an AI has no possibility of escape, will go in an infinite loop and the game will stop responding
* If a map has no borders, it will crash
* The AIs and player can walk over bombs

What does the repo comes with:
* A CMakeLists.txt to generate a solution
* Requires SFML 2.5
* Requires lib cereal


Gameplay\
![](https://i.imgur.com/322GcJi.png)\
Map Editor\
![](https://i.imgur.com/S3SFf7g.png)
