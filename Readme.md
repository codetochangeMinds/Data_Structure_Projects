## Problem Statement
Given the set of cities, flights across them, cost of flights and the time constraint, the given program should output the route optimizing the cost of the trip planned by the user in line to the time constraint. Similar to real world scenario the flight may follow a intermediate station in which it may wait for considerable amount of time.

## Solution Description
We modeled the problem into graph theory problem where cities represented the vertices's and the trip between the cities depicts an edge. We applied the Dijkstra algorithm to find the trip optimizing the cost. We also took care of the time constraint specified by the user, based on these informations the user was presented with the minimum price of the trip. The time complexity for the program is approximately O(nlogn).
