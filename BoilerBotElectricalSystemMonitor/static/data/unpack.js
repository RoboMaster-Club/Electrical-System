const MAPPING = {
    'c': {
        size: 1,
        converter: Uint8Array
    },
    '?': {
        size: 2,
        converter: Uint16Array
    },
    'f': {
        size: 4,
        converter: Float32Array
    },
    'h': {
        size: 2,
        converter: Int16Array
    },
    'H': {
        size: 2,
        converter: Uint16Array
    },
    'i': {
        size: 4,
        converter: Int32Array
    },
    'I': {
        size: 4,
        converter: Uint32Array
    },
    'd': {
        size: 1,
        converter: Float64Array
    }
};

function unpack(buffer, format, bigendian = false) {
    // Buffer: ArrayBuffer
    // Format: buffer format string, like cstruct in Python
    // bigendian: is input buffer in bigendian format
    // assume that machine is in littleendian
    var pointer = 0;
    var resultArray = [];
    for (let index = 0; index < format.length; index++) {
        let t = format.charAt(index);
        let byteLength = MAPPING[t].size;
        var bytes = buffer.slice(pointer, pointer + byteLength);
        if (bigendian)
            bytes = bytes.reverse();
        var result = new MAPPING[t].converter(bytes)[0];
        resultArray.push(result);
        pointer += byteLength;
    }
    return resultArray;
}