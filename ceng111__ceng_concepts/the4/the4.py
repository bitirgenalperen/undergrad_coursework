# -*- coding: utf-8 -*-
"""
Created on Tue Jan 14 11:57:46 2020

@author: mergen
"""

def recursiveFunc(p_list, root, graph, rootGraph, myRoot):
    edges = []
    for i in range(1, len(p_list)):
        myRoot[p_list[0]]=root
        if type(p_list[i]) == list:
            edges.append(p_list[i][0])
            recursiveFunc(p_list[i], p_list[0], graph, rootGraph, myRoot)
        else:
            edges.append(p_list[1])
            rootGraph[p_list[0]] = p_list[1]
        graph[p_list[0]] = edges

    maxValue = 0
    if type(p_list[1]) != int: #non-leaf
        for i in range(1, len(p_list)):
            maxValue  = max(maxValue, rootGraph[p_list[i][0]])
        rootGraph[p_list[0]]=maxValue


def chalchiuhtlicue(myList):
    graph= {}
    rootGraph={}
    myRoot = {}

    recursiveFunc(myList, myList[0], graph, rootGraph, myRoot)

    time = 1
    closeAll = []
    while time - 1 != rootGraph[myList[0]]:
        close = []
        for key, value in rootGraph.items():
            if value == time:
                root = key
                if value < rootGraph[myRoot[key]]:
                    close.append(key)
                else:
                    notReachedTop= True
                    if root == myList[0]:
                        notReachedTop= False
                    while rootGraph[root] == rootGraph[myRoot[root]] and notReachedTop:
                        root = myRoot[root]
                        if root == myList[0]:
                            notReachedTop= False
                    if root == myList[0]:
                        close.append(root)
                        break

        closeAll.append(close)
        time+=1

    return closeAll
