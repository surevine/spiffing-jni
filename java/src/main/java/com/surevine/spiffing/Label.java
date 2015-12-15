/*
 * Copyright 2015 Surevine Ltd
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

public class Label {
    public Label(String base64) throws SIOException {
        init(base64);
    }
    public void dispose() throws SIOException {
        dispose_n();
    }
    public native String displayMarking() throws SIOException;
    public native String fgColour() throws SIOException;
    public native String bgColour() throws SIOException;
    public native String toESSBase64() throws SIOException;
    public Spif policy() throws SIOException {
        return new Spif(policy_n());
    }
    public native boolean valid() throws SIOException;

    private long m_handle;
    private native void init(String base64) throws SIOException;
    private native void dispose_n() throws SIOException;
    private native long policy_n() throws SIOException;
}
