From: gewell@microtransgames.com

Hello,

my name is Nabe Gewell, I'm the CEO of Microtrans Games. My CTO, Cohn Jarmack, recommended you to me for having an impressive track record of saving sinking ships, if you know what I mean. Perhaps you can help us with our little problem as well. In fact, some time ago I hired a group of rockstar devs to work on our new game, Ryskim. Despite paying them a fortune (like nearly a third of what our marketing people and controllers earn), they completely messed up. 

I'll give you access to the codebase Ada Typical, Bilbo Bellic and Cro Magnon wrote.

Specifically, those are the issues I'd like you to look into:

## 1. DRM
A. Typical was tasked with the most important aspect of the game - the copy protection. My CTO told me she was using a mechanism which was used two decades ago and doesn't provide a great user experience. But I'm actually more worried that the implementation itself might be subpar. 

You can find A. Typical's work in src/drm.h and src/drm.cpp. I think Cohn also left some sour comment in main.cpp, perhaps it can help. It seems A. Typical is coming from a C background and only partially adopted C++ practices.

Could you please investigate the following points:

### 1.1. Analyze binary

Suppose the user has access to the binary, can you circumvent the copy protection? Perhaps with a hex editor or similar?
You can download a binary here: [ryskim.exe](https://github.com/m-toman/osue_exercise1/raw/gh-pages/ryskim.exe)

### 1.2. Crack

Our intern, Dorian Dactic, was tasked with writing a crack to retrieve the copy protection data from the binary automatically. Unfortunately he failed epically.
Could you fix his code and get the crack to work?
It's here: [crack_tofix.c](https://raw.githubusercontent.com/m-toman/osue_exercise1/gh-pages/crack_tofix.c)

(It's just reading out the binary. It would be great to have something that overrides the JMP to the DRM check with a NOP to have a real crack, but this is NOT part of our contract.)

### 1.3. Without access to the binary

Now let's assume the user doesn't have access to the binary itself but can run Ryskim, like on a console or a game streaming service. Or the DRM is actually verified on the server. Cohn thinks a buffer overflow should be able to crack that easily.
Could you give suggestions on how to improve this code?

You can find the relevant code pieces here:
- [https://github.com/m-toman/osue_exercise1/blob/master/src/drm.h](https://github.com/m-toman/osue_exercise1/blob/master/src/drm.h)
- [https://github.com/m-toman/osue_exercise1/blob/master/src/drm.cpp](https://github.com/m-toman/osue_exercise1/blob/master/src/drm.cpp)


## 2. Memory issues

B. Bellic was responsible for the game logic. The testers found that the game sucks up lots of memory after just 20 hours of gaming. According to our statistics, typical sessions of our gamers last 34.3 hours, on average.
Might be a memory leak or some similar issue.

Could you please check src/game.h and src/game.cpp if there is some issue with the game logic that could lead to memory usage going up over time.

Also, could you suggest quick fixes for the problems you encounter - and ideally also general architecture improvements to avoid such issues in future?

You can download and build the whole repository from here:
[https://github.com/m-toman/osue_exercise1](https://github.com/m-toman/osue_exercise1)
