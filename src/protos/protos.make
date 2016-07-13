all:	
	@echo Protos ...
	# CPP OUTPUT FILES
	@protoc -I=. --cpp_out=. state.proto
	@protoc -I=. --cpp_out=. command.proto

	# JAVA OUTPUT FILES
	@protoc -I=. --java_out=. state.proto
	@protoc -I=. --java_out=. command.proto

	# CSharp OUTPUT FILES
	#@protoc -I=. --csharp_out=. state.proto
	#@protoc -I=. --csharp_out=. command.proto