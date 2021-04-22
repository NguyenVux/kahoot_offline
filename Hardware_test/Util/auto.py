Import("env")
test = input("Enter number")
env.Append(CPPDEFINES="-D test")
env.Append(CPPDEFINES="-D binary_test=0x"+test)