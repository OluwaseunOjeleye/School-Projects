Library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

Entity BCD_7SDD is
  Port ( 
    X: in std_logic_Vector(3 DOWNTO 0);
    F: out std_logic_Vector(6 DOWNTO 0)
  );
End BCD_7SDD;

--X3-A X2-B X1-C X0-D

Architecture Behv of BCD_7SDD is
Begin
  F(6) <= X(3) OR X(1) OR (X(2) AND X(0)) OR (NOT X(2) AND NOT X(0));  --A
  F(5) <= (NOT X(2)) OR (NOT X(1) AND NOT X(0)) OR (X(1) AND X(0));  --B
  F(4)<= X(2) OR NOT X(1) OR X(0);--C
  F(3)<= (NOT X(2) AND NOT X(0)) OR (X(1) AND NOT X(0)) OR (X(2) AND NOT X(1) AND X(0)) OR (NOT X(2) AND X(1)) OR X(3);--D
  F(2)<= (NOT X(2) AND NOT X(0)) OR (X(1) AND NOT X(0));--E
  F(1)<= X(3) OR (NOT X(1) AND NOT X(0)) OR (X(2) AND NOT X(1)) OR (X(2) AND NOT X(0));--F
  F(0)<= X(3) OR (X(2) AND NOT X(1)) OR ( NOT X(2) AND X(1)) OR (X(1) AND NOT X(0));--G
End Behv;