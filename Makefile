all: parse_text

parse_text:
	g++ -std=c++11 parse_text.cpp -o parse_text

clean:
	rm parse_text 
