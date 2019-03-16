From: gewell@microtransgames.com

Hello,

my name is Nabe Gewell, I'm the CEO of Microtrans Games. My CTO, Cohn Jarmack, recommended you to me for having an impressive track record of saving sinking ships, if you know what I mean. Perhaps you can help us with our little problem as well. In fact, some time ago I hired a group of rockstar devs to work on our new game, Ryskim. Despite paying them a fortune (like nearly a third of what our marketing people and controllers earn), they completely messed up. 

I'll give you access to the codebase Ada Typical, Bilbo Bellic and Cro Magnon wrote.

Specifically, those are the issues I'd like you to look into:

## 1. DRM
A. Typical was tasked with the most important aspect of the game - the copy protection. My CTO told me she was using a mechanism which was used two decades ago and doesn't provide a great user experience. But I'm actually more worried that the implementation itself might be subpar. Could you check if it's possible to circumvent the copy protection in two cases:

- The user has access to the binary.
- The user does not have access to the binary, so when Ryskim is running on a closed system like a console or some server.

You can find A. Typical's work in src/drm.h and src/drm.cpp. I think Cohn also left some sour comment in main.cpp, perhaps it can help. It seems A. Typical is coming from a C background and only partially adopted C++ practices.

Can you give suggestions on how to improve this?


## 2. Memory issues

B. Bellic was responsible for the game logic. The testers found that the game sucks up lots of memory after just 20 hours of gaming. Might be a memory leak or some similar issue.
So please check src/game.h and src/game.cpp if there is some issue with the game logic that could lead to memory usage going up over time (Hint: check elements that are created and destroyed over the game lifetime).

Could you suggest quick fixes or the problems you encounter and ideally also general architecture improvements to avoid such issues in future?
