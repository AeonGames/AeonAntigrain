## Aeon Games Fork of The Anti-Grain Geometry Library

A high quality rendering engine for C++

This is a fork of the Anti-Grain Geometry graphics library
with the goal to mantain the library usability in the future.

All changes made under the Aeon Games repository should be considered
as covered by the Apache 2.0 license, however all unmodified code
shall remain under the original license, no copyright notices shall be
removed until none of the original code remains, but additional
copyright notices shall be put in place to diferentiate modified
compilation units.

Anti-Grain Geometry - Version 2.4
Copyright (C) 2002-2005 Maxim Shemanarev (McSeem)

Permission to copy, use, modify, sell and distribute this software
is granted provided this copyright notice appears in all copies.
This software is provided "as is" without express or implied
warranty, and with no claim as to its suitability for any purpose.

## History

From [https://en.wikipedia.org/wiki/Anti-Grain_Geometry#History](Wikipedia) (6/10/2019):

>Active development of the AGG codebase stalled in 2006, around the time of the v2.5 release, due to shifting priorities of its primary developer Maxim Shemanarev. Shemanarev remained active in the community until his sudden death in November, 2013. Development has continued on a fork of the more liberally licensed v2.4 on SourceForge.net.

This is a fork of said sourceforge repository.

## What to expect from this fork

### Expect

- Refactoring: Most of it with the goal to bring the code up to modern C++ standards.
- Dynamic library support: The original code only generated static libraries, this fork won't.
- Multithreading support: If not already present.
- GPU assisted support: TBD.
- Limited Support: While it would be nice to implement all suggestions and fix all bugs, Antigrain is not our priority.
- Eager Push Request/Issue attention: If you find a bug or add a feature please submit an Issue or Pull request.
- Open Source that does not restrict usage: If you file a PR, you must agree to your source being under the Apache 2.0 lineaments.
- Recognition: If you contribute to the project please make sure to add your own copyright notice next to your name in the files you changed.

### Do NOT expect

- Fast development time: The project may lay dormant for long periods as this is not our focus.
- Drop in replacement with the original code (for too long): We may need to make changes and cannot promise the API to remain backward compatible to version 2.4.
- Staying away from the STL: C++ has come a long way since 2005, STL containers are no longer worse than anything a single person can come up with.
