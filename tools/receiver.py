import struct

def main():
    import socket
    host = "localhost"
    port = 50000

    serversock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serversock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serversock.bind((host, port))
    serversock.listen(1)

    print 'Waiting for connections at ({}, {})\n'.format(host, port)

    clientsock, client_address = serversock.accept()

    while True:
        buffer = bytearray(b' ' * 4096)
        nBytes = clientsock.recv_into(buffer)

        if nBytes == 0:
            continue

        size_array, address_array, type_array, arg_array = split_packet(buffer[:nBytes])
        size = read_size_array(size_array)

        args = read_args(type_array, arg_array)
        print args

    clientsock.close()


def split_packet(buffer):
    size_array = buffer[:4]
    address_array, type_arg_array = buffer[4:].split(b",", 1)
    type_end_at = type_arg_array.index(chr(0))
    arg_start_at = ((type_end_at / 4) + 1) * 4 - 1  # minus one for comma
    type_array = type_arg_array[:type_end_at]
    arg_array = type_arg_array[arg_start_at:]
    return size_array, address_array, type_array, arg_array


def read_size_array(size_array):
    sum = 0
    for i, c in enumerate(reversed(size_array)):
        sum += int(c) * pow(256, i)
    return sum


def read_args(type_array, arg_array):
    args = []
    offset = 0
    size = 0
    for type_byte in type_array:
        type_str = chr(type_byte)
        if type_str == "i":
            size = 4
            data = arg_array[offset:offset+size]
            arg_struct = struct.pack("!cccc", *[chr(i) for i in data])
            args.append(struct.unpack("!i", arg_struct)[0])
        elif type_str == "f":
            size = 4
            data = arg_array[offset:offset+size]
            arg_struct = struct.pack("!cccc", *[chr(i) for i in data])
            args.append(struct.unpack("!f", arg_struct)[0])
        elif type_str == "h":
            size = 8
            data = arg_array[offset:offset+size]            
            arg_struct = struct.pack("!cccccccc", *[chr(i) for i in data])
            args.append(struct.unpack("!q", arg_struct)[0])
        elif type_str == "s":
            size = arg_array[offset:].index(chr(0))
            data = arg_array[offset:offset+size]            
            format_str = "!" + "c" * size
            arg_struct = struct.pack(format_str, *[chr(i) for i in data])
            format_str = "!" + str(size) + "s"
            arg = struct.unpack(format_str, arg_struct)[0]
            args.append(arg)
            numZeros = 4 - size % 4
            size += numZeros

        offset += size

    return args


if __name__ == "__main__":
    main()
