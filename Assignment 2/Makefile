
CFLAGS = -g  

final: main.cpp hcmcampaign.cpp
	echo "Combine everything"
	@clang++ $(CFLAGS) main.cpp hcmcampaign.cpp -o final.exe

run: final.exe
	echo "Execute final"
	@./final.exe

clean:
	echo "Remove all but the source files"
	@rm -f final.exe