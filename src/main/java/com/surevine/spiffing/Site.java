package com.surevine.spiffing;

/**
 * Copyright
 *
 * Surevine/MIT
 */
public class Site {
    private native void init();
    public Site() {
        init();
    }
    private native long spif_native(String oid);
    public Spif spif(String oid) {
        return new Spif(spif_native(oid));
    }
    private native long load_native(String filename);
    public Spif load(String filename) {
        return new Spif(load_native(filename));
    }
    public static Site site() {
        if (s_instance == null) {
            s_instance = new Site();
        }
        return s_instance;
    }
    private native void dispose_native();
    public void dispose() {
        dispose_native();
        if (s_instance != null) {
            s_instance = null;
        }
    }
    private static Site s_instance;
    private static long m_handle;
}
