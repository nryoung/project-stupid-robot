----------------------------------------------------------------------------------
-- Company: Digilent Ro
-- Engineer: Tudor Armand Ciuleanu
-- 
-- Create Date:   10:57:00 02/28/2008
-- Module Name:   SoundGenerator.vhd
-- Project Name: 	LS1 Reference Project
-- Tool versions: Xilinx ISE 9.2
-- Description: 	Generates a sinus wave by adding the 4 sinus waves obtained from
--			the cordic generators. A sinus wave is added only if the coresponding 
--			input from PmodLS1 is HIGH. 
--
-- Revision: 
-- Revision 0.01 - File Created
-- 
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.std_logic_signed.all;

library UNISIM;
use UNISIM.VComponents.all;

entity SoundGenerator is
    Port ( ck 			: in  STD_LOGIC;							--50 mhz clock input
           LSData 	: in  STD_LOGIC_VECTOR (3 downto 0);--4 inputs from LS1
           SoundOut 	: out  STD_LOGIC_VECTOR (11 downto 0)--12 bit value representing
										--a sample of the final sin wave
			  );
end SoundGenerator;

architecture Behavioral of SoundGenerator is

component Cordic is
    port (
        ck: in std_logic;
        x: 	inout std_logic_vector (9 downto 0)
    );
end component;

--values used for clock dividing to obtain 4 different frequencies
--which correspod to 4 musical notes
-- C -  523Hz - divide 50 MHz by 956
-- E -  659Hz - divide 50 MHz by 758
-- G -  784Hz - divide 50 MHz by 638
-- C - 1046Hz - divide 50 MHz by 478

constant divA: integer:= 956;--C
constant divB: integer:= 758;--E
constant divC: integer:= 638;--G
constant divD: integer:= 478;--C

--signals used for the 4 counters which are used to obtain the needed frequencies
signal cntDivA: integer; 
signal cntDivB: integer;
signal cntDivC: integer;
signal cntDivD: integer;

--signals obtained after dividing the clock used as inputs for BUFG's
signal ckA_int: std_logic;
signal ckB_int: std_logic;
signal ckC_int: std_logic;
signal ckD_int: std_logic;

--clock signals obtained from the otput of the BUFG's, used as
--inputs for the cordic sin wave generators
signal ckA: std_logic;
signal ckB: std_logic;
signal ckC: std_logic;
signal ckD: std_logic;

--10 bit samples obtained from the cordic sin wave generators
signal SoundA: std_logic_vector(9 downto 0);
signal SoundB: std_logic_vector(9 downto 0);
signal SoundC: std_logic_vector(9 downto 0);
signal SoundD: std_logic_vector(9 downto 0);

--12 bit sample which take the value of SoundA,SoundB,SoundC,SoundD
--if the coresponding input from LS1 is active else the value will be 0.
--The extension from 10 to 12 bits is made by extending the sign of the
--10 bit value by copying the 10th bit on the 11th and 12th position.
--This is needed because the DA2 doesn't work with signed numbers
signal Sound_intA: std_logic_vector(11 downto 0):="000000000000";
signal Sound_intB: std_logic_vector(11 downto 0):="000000000000";
signal Sound_intC: std_logic_vector(11 downto 0):="000000000000";
signal Sound_intD: std_logic_vector(11 downto 0):="000000000000";

--resulting sin wave after adding the 4 intermediate signals
signal Sound_int: std_logic_vector(11 downto 0):="000000000000";

begin


--the folowing proccess is a clock divider which divides the 50 MHz
--frequency to a 523Hz one
ckDividerA: process(ck)
		begin
			if ck'event and ck='1' then
				if cntDivA = divA-1 then
					cntDivA <= 0;
					ckA_int <= '1';
				else
					cntDivA <= cntDivA + 1;
					ckA_int <='0';
				end if;
			end if;
		end process;
	
	BUFG_instA : BUFG
   port map (
      O => ckA,     		-- Clock buffer output
      I => ckA_int	   -- Clock buffer input
   );

--using the clock signal obtained from the divider the cordic
--module will return a value of a sample from the sin wave
--coresponding to this sound
	Cordic_instA: Cordic 
	port map(
		ck => ckA,
		x => SoundA
	);

--the folowing proccess is a clock divider which divides the 50 MHz
--frequency to a 659Hz one
ckDividerB: process(ck)
		begin
			if ck'event and ck='1' then
				if cntDivB = divB-1 then
					cntDivB <= 0;
					ckB_int <= '1';
				else
					cntDivB <= cntDivB + 1;
					ckB_int <='0';
				end if;
			end if;
		end process;
	
	BUFG_instB : BUFG
   port map (
      O => ckB,    	 	-- Clock buffer output
      I => ckB_int	   -- Clock buffer input
   );

--using the clock signal obtained from the divider the cordic
--module will return a value of a sample from the sin wave
--coresponding to this sound
	Cordic_instB: Cordic 
	port map(
		ck => ckB,
		x => SoundB
	);


--the folowing proccess is a clock divider which divides the 50 MHz
--frequency to a 784Hz one
ckDividerC: process(ck)
		begin
			if ck'event and ck='1' then
				if cntDivC = divC-1 then
					cntDivC <= 0;
					ckC_int <= '1';
				else
					cntDivC <= cntDivC + 1;
					ckC_int <='0';
				end if;
			end if;
		end process;
	
	BUFG_instC : BUFG
   port map (
      O => ckC,     		-- Clock buffer output
      I => ckC_int	   -- Clock buffer input
   );

--using the clock signal obtained from the divider the cordic
--module will return a value of a sample from the sin wave
--coresponding to this sound
	Cordic_instC: Cordic 
	port map(
		ck => ckC,
		x => SoundC
	);
	
	
--the folowing proccess is a clock divider which divides the 50 MHz
--frequency to a 1046Hz one
ckDividerD: process(ck)
		begin
			if ck'event and ck='1' then
				if cntDivD = divD-1 then
					cntDivD <= 0;
					ckD_int <= '1';
				else
					cntDivD <= cntDivD + 1;
					ckD_int <='0';
				end if;
			end if;
		end process;
	
	BUFG_instD : BUFG
   port map (
      O => ckD,     		-- Clock buffer output
      I => ckD_int	   -- Clock buffer input
   );

--using the clock signal obtained from the divider the cordic
--module will return a value of a sample from the sin wave
--coresponding to this sound
	Cordic_instD: Cordic 
	port map(
		ck => ckD,
		x => SoundD
	);
	

--If the coresponding input from LSData(0) is High Sound_intA will take the
--value of the sample from the cordic module else it will be 0.
--The extension from 10 to 12 bits is made by extending the sign of the
--10 bit value SoundA by copying the 10th bit on the 11th and 12th position.
procSoundA:process(LSData(0))
	begin
			if LSData(0) = '1' then
				Sound_intA <= SoundA(9) & SoundA(9) & SoundA(9 downto 0);
			else
				Sound_intA <= "000000000000";
			end if;
	end process;

--same as above
procSoundB:process(LSData(1))
	begin
			if LSData(1) = '1' then
				Sound_intB <= SoundB(9) & SoundB(9) & SoundB(9 downto 0);
			else
				Sound_intB <= "000000000000";
			end if;
	end process;
	
--same as above
procSoundC:process(LSData(2))
	begin
			if LSData(2) = '1' then
				Sound_intC <= SoundC(9) & SoundC(9) & SoundC(9 downto 0);
			else
				Sound_intC <= "000000000000";
			end if;
	end process;
	
--same as above
procSoundD:process(LSData(3))
	begin
			if LSData(3) = '1' then
				Sound_intD <= SoundD(9) & SoundD(9) & SoundD(9 downto 0);
			else
				Sound_intD <= "000000000000";
			end if;
	end process;
	
	
--the four resulting sinus waves are added together 
	Sound_int <= Sound_intA+Sound_intB+Sound_intC+Sound_intD;
	
--the first bit of the output wave has to be complemented because
--the DA2 works only with unsigned numbers
	SoundOut <= (not sound_int(11)) & Sound_int(10 downto 0);
	 	
end Behavioral;

