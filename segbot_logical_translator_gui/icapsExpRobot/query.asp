h(eql(visited(P),false),0). 
h(eql(served(P),false),0). 

:- v_approach(D,V_astep-1), not callforopen(D,V_astep).
:- v_callforopen(D,V_astep-1), not gothrough(D,V_astep).
:- v_gothrough(D,V_astep-1), approach(D,V_astep).

-noop(V_step) :- approach(D,V_step).
-noop(V_step) :- gothrough(D,V_step).
-noop(V_step) :- callforopen(D,V_step).
-noop(V_step) :- sense(P1,ploc(P2),V_step).
-noop(V_step) :- goto(P,V_step).

noop(V_step) :- not -noop(V_step).

v_approach(D,V_astep) :- approach(D,V_astep).
v_approach(D,V_astep) :- v_approach(D,V_astep-1), noop(V_astep).
v_callforopen(D,V_astep) :- callforopen(D,V_astep).
v_callforopen(D,V_astep) :- v_callforopen(D,V_astep-1), noop(V_astep).
v_gothrough(D,V_astep) :- gothrough(D,V_astep).
v_gothrough(D,V_astep) :- v_gothrough(D,V_astep-1), noop(V_astep).


%:- approach(Y,V_step),at(X,V_step), acc(X,Y,Z), 1{hasdoor(Z,N)}1, inside(peterstone,W,V_step), Z!=W.


%goal: serve everyone to collect their mail
goal(0,V_step) :- h(eql(served(alice),true),V_step).
goal(1,V_step) :- h(eql(served(bob),true),V_step).
goal(2,V_step) :- h(eql(served(carol),true),V_step).
goal(3,V_step) :- h(eql(served(dan),true),V_step).
goal(4,V_step) :- h(eql(served(erin),true),V_step).
goal(5,V_step) :- h(eql(served(frank),true),V_step).
goal(6,V_step) :- h(eql(served(george),true),V_step).
goal(7,V_step) :- h(eql(served(harry),true),V_step).
goal(8,V_step) :- h(eql(served(ian),true),V_step).
goal(9,V_step) :- h(eql(served(jack),true),V_step).



goal(G,V_astep) :- goal(G,V_astep-1).

false :- not goal(1,maxstep).
false :- not goal(2,maxstep).
false :- not goal(3,maxstep).
false :- not goal(4,maxstep).
false :- not goal(5,maxstep).
false :- not goal(6,maxstep).
false :- not goal(7,maxstep).
false :- not goal(8,maxstep).
false :- not goal(9,maxstep).
false :- not goal(0,maxstep).

true.
:- false.


