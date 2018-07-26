
This library contains C code to implement the Blackmagic SDI Camera
Control Protocol, a control system by which a PC equipped with a
BlackMagic Decklink card --- or the Blackmagic Arduino shield --- can
send remote control commands to Blackmagic cameras through an SDI
loop.

This library deals strictly with forming messages, not with
putting the data out to the camera --- as such it does not require the
Blackmagic API.

While the library itself is written in C, the test suite uses [gtest](), which is C++-based.


= Usage

There are two main classes.   A `BMSDIBuffer` is a 255-byte buffer with an index.  A `BMSDIMessage` is a single SDI Control message which is created by mapping
onto the body of a buffer.

An example:

    ...

    BMSDIBuffer *buffer = bmNewBuffer();
    BMSDIMessage *msg = bmAddConfigMessage( buffer,
                                            camAddr,
                                            BM_CAT_LENS,
                                            BM_PARAM_FOCUS,
                                            BM_OP_ASSIGN,
                                            BM_TYPE_FIXED16,
                                            1 );
    bmConfigWriteFixed16( msg, 1.0 );

    // Message is now encoded in buffer->data

    ...

This creates an empty buffer.  Within buffer it adds a "config" message (at present the only type of message available, though the API leaves room for others).
The header if the message is pre-loaded with the message type (`config`), the category (Lens) the parameter (Focus), the operation type (Assign), and the type and number of paramters (one 16-bit fixed, a format proprietary to the protocol).

Additional messages can appended to added to the buffer.   `bmAddConfigMessage` will return NULL if the buffer becomes full ... but the previously-added messages in
the buffer will not be affected.

`libbmsdi/protocol.h` contains `#defines`s and notes for many/most of the
constants in the protocol.


= Notes on the Blackmagic SDI Camera Control Protocol


Important to remember this protocol is used for data _to_ the camera.


From _"Installation and Operation Manual; Blackmagic Studio Cameras; November 2017"_


== Assumptions

Alignment and padding constraints are explicitly described in the protocol document. Bit fields are packed from LSB first. Message groups, individual messages and command headers are defined as, and can be assumed to be, 32 bit aligned.

== Blanking Encoding

A message group is encoded into a SMPTE 291M packet with DID/SDID x51/x53 in the active region of VANC line 16.

== Message Grouping

Up to 32 messages may be concatenated and transmitted in one blanking packet up to a maximum of 255 bytes payload. Under most circumstances, this should allow all messages to be sent with a maximum of one frame latency.

If the transmitting device queues more bytes of message packets than can be sent in a single frame, it should use heuristics to determine which packets to prioritize and send immediately. Lower priority messages can be delayed to later frames, or dropped entirely as appropriate.

== Abstract Message Packet Format

Every message packet consists of a three byte header followed by an optional variable length data block. The maximum packet size is 64 bytes.

* Destination device (uint8)
*
Device addresses are represented as an 8 bit unsigned integer. Individual devices are numbered 0 through 254 with the value 255 reserved to indicate a broadcast message to all devices.

* Command length (uint8)

The command length is an 8 bit unsigned integer which specifies the length of the included command data. The length does NOT include the length of the header or any trailing padding bytes.

* Command id (uint8)

The command id is an 8 bit unsigned integer which indicates the message type being sent. Receiving devices should ignore any commands that they do not understand. Commands 0 through 127 are reserved for commands that apply to multiple types of devices. Commands 128 through 255 are device specific.

* Reserved (uint8)

This byte is reserved for alignment and expansion purposes. It should be set to zero.

* Command data(uint8[])

The command data may contain between 0 and 60 bytes of data. The format of the data section is defined by the command itself.

* Padding(uint8[])

Messages must be padded up to a 32 bit boundary with 0x0 bytes. Any padding bytes are NOT included in the command length.

Receiving devices should use the destination device address and or the command identifier to determine which messages to process. The receiver should use the command length to skip irrelevant or unknown commands and should be careful to skip the implicit padding as well.
