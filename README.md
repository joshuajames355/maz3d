# maz3d

A maze game written in UE4 using c++ and blueprints for DURHACK 2020. Levels are generated using an external python script (decoded in maz3d/Source/maz3d/MapGeneratorGamemode.cpp), and position/level data is broadcast to a game server over tcp (maz3d/Source/maz3d/TcpConnection.cpp), so progress can be tracked via an external webapp.
