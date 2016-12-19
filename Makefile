conv: conv.cpp json/json.h json/json-forwards.h jsoncpp.cpp
		g++ conv.cpp jsoncpp.cpp -lcurl -o conv

clean: conv
	rm -fr conv
	rm -fr body.out