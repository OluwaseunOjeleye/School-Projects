library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

Entity Full_adder is
	Port ( 
	 A : in STD_LOGIC;
	 B : in STD_LOGIC;
	 Cin : in STD_LOGIC;
	 S : out STD_LOGIC;
	 Cout : out STD_LOGIC);
End Full_adder;

Architecture test of Full_adder is
Begin
	S <= A XOR B XOR Cin ;
	Cout <= (A AND B) OR (Cin AND A) OR (Cin AND B) ;
End test;



