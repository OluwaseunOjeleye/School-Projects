Library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

Entity FSM is
  Port(
    clk:in std_logic;
    X: in std_logic_Vector(1 DOWNTO 0);
    F: out std_logic 
  );
End FSM;

Architecture Behv of FSM is
Type States is (START, WASH, RINSE, SQUEEZE);
Signal Pre_State: States:=Start;
Begin
Process(clk)
Begin
  if(Rising_edge(clk)) then
    Case Pre_State is
      When START=>
        if(X="00") Then
          F<='0';
          Pre_State<=WASH;
        elsif(X="01") Then
          F<='0';
          Pre_State<=RINSE;
        elsif(X="10") Then
          F<='0';
          Pre_State<=SQUEEZE;
        end if;
        
      When WASH=>
        if(X="01") Then
          F<='0';
          Pre_State<=RINSE;
        elsif(X="11") Then
          F<='0';
          Pre_State<=START;
        end if;
    
      When RINSE=>
        if(X="10") Then
          F<='0';
          Pre_State<=SQUEEZE;
        elsif(X="11") Then
          F<='0';
          Pre_State<=START;
        end if;
  
      When SQUEEZE=>
        F<='1';
        if(X="11") Then
          F<='0';
          Pre_State<=START;
        end if;
    end case;
  end if;
end process;
end Behv;