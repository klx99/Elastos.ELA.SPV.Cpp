//  Created by Ed Gamble on 1/23/2018
//  Copyright (c) 2018 breadwallet LLC.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#include <BRMerkleBlock.h>
#include <assert.h>
#include "BRCoreJni.h"
#include "BRMerkleBlock.h"
#include "com_elastos_spvcore_CoreMerkleBlock.h"

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    createJniCoreMerkleBlock
 * Signature: ([BI)J
 */
JNIEXPORT jlong JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_createJniCoreMerkleBlock
(JNIEnv *env, jclass thisClass,
 jbyteArray blockArray,
 jint blockHeight) {

	int blockLength   = (*env)->GetArrayLength(env, blockArray);
	jbyte *blockBytes = (*env)->GetByteArrayElements(env, blockArray, 0);

	assert (NULL != blockBytes);
	BRMerkleBlock *block = BRMerkleBlockParse((const uint8_t *) blockBytes, (size_t) blockLength);
	assert (NULL != block);
	if (blockHeight != -1)
		block->height = (uint32_t) blockHeight;

	return (jlong) block;
}

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    createJniCoreMerkleBlockEmpty
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_elastos_spvcore_CoreMerkleBlock_createJniCoreMerkleBlockEmpty
(JNIEnv *env, jclass thisClass) {
	// Test only
	BRMerkleBlock *block = BRMerkleBlockNew();
	block->height = BLOCK_UNKNOWN_HEIGHT;
	return (jlong) block;
}


/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    getBlockHash
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_getBlockHash
(JNIEnv *env, jobject thisObject) {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);

	UInt256 hash = block->blockHash;

	jbyteArray hashObject = (*env)->NewByteArray (env, sizeof (UInt256));
	(*env)->SetByteArrayRegion (env, hashObject, 0, sizeof (UInt256), (const jbyte *) hash.u8);
	return hashObject;
}

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    getVersion
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_getVersion
(JNIEnv *env, jobject thisObject)  {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);
	return (jlong) block->version;
}

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    getPrevBlockHash
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_getPrevBlockHash
(JNIEnv *env, jobject thisObject) {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);

	UInt256 hash = block->prevBlock;

	jbyteArray hashObject = (*env)->NewByteArray (env, sizeof (UInt256));
	(*env)->SetByteArrayRegion (env, hashObject, 0, sizeof (UInt256), (const jbyte *) hash.u8);
	return hashObject;
}

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    getRootBlockHash
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_getRootBlockHash
(JNIEnv *env, jobject thisObject) {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);

	UInt256 hash = block->merkleRoot;

	jbyteArray hashObject = (*env)->NewByteArray (env, sizeof (UInt256));
	(*env)->SetByteArrayRegion (env, hashObject, 0, sizeof (UInt256), (const jbyte *) hash.u8);
	return hashObject;
}

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    getTimestamp
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_getTimestamp
(JNIEnv *env, jobject thisObject) {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);
	return (jlong) block->timestamp;
}

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    getTarget
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_getTarget
(JNIEnv *env, jobject thisObject) {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);
	return (jlong) block->target;
}

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    getNonce
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_getNonce
(JNIEnv *env, jobject thisObject) {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);
	return (jlong) block->nonce;
}

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    getTransactionCount
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_getTransactionCount
(JNIEnv *env, jobject thisObject) {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);
	return (jlong) block->totalTx;
}

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    getHeight
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_getHeight
(JNIEnv *env, jobject thisObject) {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);
	return (jlong) block->height;
}

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    serialize
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_elastos_spvcore_CoreMerkleBlock_serialize
(JNIEnv *env, jobject thisObject) {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);

	size_t      byteArraySize     = BRMerkleBlockSerialize(block, NULL, 0);
	jbyteArray  byteArray         = (*env)->NewByteArray (env, (jsize) byteArraySize);
	jbyte      *byteArrayElements = (*env)->GetByteArrayElements (env, byteArray, JNI_FALSE);

	BRMerkleBlockSerialize(block, (uint8_t *) byteArrayElements, byteArraySize);

	// Ensure ELEMENTS 'written' back to byteArray
	(*env)->ReleaseByteArrayElements (env, byteArray, byteArrayElements, JNI_COMMIT);

	return byteArray;
}


/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    isValid
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_isValid
(JNIEnv *env, jobject thisObject, jlong currentTime) {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);
	return (jboolean) BRMerkleBlockIsValid (block, (uint32_t) currentTime);
}

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    containsTransactionHash
 * Signature: ([B)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_containsTransactionHash
(JNIEnv *env, jobject thisObject, jbyteArray hashByteArray) {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);

	UInt256 *hash = (UInt256 *) (*env)->GetByteArrayElements (env, hashByteArray, JNI_FALSE);
	return (jboolean) BRMerkleBlockContainsTxHash (block, *hash);
}

/*
 * Class:     com_elastos_spvcore_CoreMerkleBlock
 * Method:    disposeNative
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_elastos_spvcore_CoreMerkleBlock_disposeNative
(JNIEnv *env, jobject thisObject) {
	BRMerkleBlock *block = (BRMerkleBlock *) getJNIReference(env, thisObject);
	if (NULL != block) BRMerkleBlockFree(block);
}

