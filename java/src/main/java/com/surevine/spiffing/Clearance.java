/*
 * Copyright 2016 Surevine Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * (These are the standard Surevine/MIT terms)
 */

package com.surevine.spiffing;

/**
 * Created by dwd on 14/11/15.
 */
public class Clearance implements AutoCloseable {
    public Clearance(String base64) throws SIOException {
        init(base64);
    }
    public native String displayMarking() throws SIOException;
    public native boolean dominates(Label l) throws SIOException;
    public native String toESSBase64() throws SIOException;
    public Spif policy() throws SIOException {
        return new Spif(policy_native());
    }

    private native long policy_native() throws SIOException;
    private native void init(String base64) throws SIOException;
    public native void dispose();
    private long m_handle;
    @Override
    public void close() throws Exception {
        dispose();
    }
}
