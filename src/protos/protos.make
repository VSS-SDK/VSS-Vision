all:	
	@echo Protos ...
	@protoc -I=. --cpp_out=. state.proto
	@protoc -I=. --cpp_out=. command.proto
