// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGeneratorGamemode.h"



FMapStruct AMapGeneratorGamemode::decodeMap(const FString& map)
{
	FMapStruct mapStruct;
	mapStruct.portals = TArray<FPortalPair>();
	mapStruct.floors = TArray<FLevela>();

	int i = 0;
	while (true)
	{
		FLevela level;
		TArray<bool> points = TArray<bool>();

		while (map[i] != '-' && map[i] != '/')
		{
			if (map[i] == '1')
			{
				points.Add(true);
			}
			if (map[i] == '0')
			{
				points.Add(false);
			}
			i += 1;
		}

		level.points = points;
		mapStruct.floors.Push(level);
		if (map[i] == '/') break;

		i += 1;
	}
	
	while (map[i] < 48 || map[i] > 57) i += 1;



	while (true)
	{
		if (i + 14 >= map.Len() || map[i] == '$') break;

		FPortalStruct in;
		FPortalStruct out;
		FPortalPair pair;

		in.maze = map[i] - 48;

		i += 2;
		in.x = map[i] - 48;

		i += 2;
		in.y = map[i] - 48;

		i += 2;
		in.rot = map[i] - 48;

		i += 2;
		out.maze = map[i] - 48;

		i += 2;
		out.x = map[i] - 48;

		i += 2;
		out.y = map[i] - 48;

		i += 2;
		out.rot = map[i] - 48;

		i += 1;
		while (i< map.Len() && map[i] == '\n' || map[i] == '\r') i += 1;

		pair.out = out;
		pair.in = in;
		mapStruct.portals.Add(pair);
	}
	return mapStruct;
}



