----------------------------------------------------------------------------------
-- Company: Digilent Ro
-- Engineer: Mircea Dabacan

-- Create Date:    10:57:00 02/28/2008
-- Module Name:    Cordic.vhd 
-- Project Name: 	 LS1ReferenceDesign
-- Tool versions:  Xilinx ISE 9.2
-- Description: Generates 10-bit digital samples of a sin-wave,
-- 100 samples/second => sin frequency is 100 times smaller than CK
-- Uses the Cordic algorithm:
-- 		x=x+y*tg(2*pi/100);	where tg(2*pi/100) =  1/16 
--			y=y-x*tg(2*pi/100);
-- result in x = A*cos(2*pi* Tck /100) and y = A*sin(2*pi* Tck /100)
-- where Tck is the process clock period and A is the amplitude, determined 
-- by the initial values of x and y (xi and yi):
-- 		A=sqr(xi*xi+yi*yi)
-- Division by 16 performed by shifting the binary number four bits to right.
--
-- Revision: 
-- Revision 0.01 - Mircea Dabacan - File Created 
--				0.02 - Tudor Armand Ciuleanu - Added the initialisation phase 
--						removed the reset signal, addapted for 10-bit samples
-- 
----------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;

entity Cordic is
    port (
        ck: in std_logic;						  		-- clock signal input
	     x: inout std_logic_vector (9 downto 0) 	-- feedback needs inout
    );
end Cordic;

architecture Cordic_arch of Cordic is

signal y: std_logic_vector (9 downto 0);
signal init: std_logic := '0';

begin

	cord: process(ck)
		variable xnew: std_logic_vector (9 downto 0);
		begin
		if init = '0' then							-- initialization phase
			x <= "0110111111";						-- initial values for x and y
			y <= "0000000000";						-- determine the sin/cos amplitude
			init <= '1';
		elsif ck'event and ck = '1' then
		
			xnew := x + y(9 downto 4);		-- xnew is a variable; its value is updated imediately
													-- previous value of y used
			x <= xnew;							-- x signal will receive the new value only in the next process instantion
			y <= y - xnew(9 downto 4);		-- updated value of xnew used
		end if;
	end process;		
end Cordic_arch;


