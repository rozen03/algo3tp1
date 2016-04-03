// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) lnc 
// Source File Name:   KaioKenTester.java

import java.io.*;
import java.security.SecureRandom;

public class KaioKenTester
{

            void generate(String s)
            {
/*  14*/        try
                {
/*  14*/            SecureRandom securerandom = SecureRandom.getInstance("SHA1PRNG");
/*  15*/            long l = Long.parseLong(s);
/*  16*/            securerandom.setSeed(l);
/*  17*/            N = securerandom.nextInt(9999) + 2;
                }
/*  20*/        catch(Exception exception)
                {
/*  21*/            addFatalError("An exception occurred while trying to get your program's results.");
/*  22*/            exception.printStackTrace();
                }
            }

            public String runTest(String s)
            {
                int ai[][];
                int i;
/*  28*/        generate(s);
/*  31*/        ai = bandos(N);
/*  34*/        i = 0;
_L1:
/*  34*/        if(i >= ai.length)
/*  35*/            break MISSING_BLOCK_LABEL_48;
/*  35*/        if(ai[i].length != N)
                {
/*  37*/            addFatalError("Todos los guerreros deben participar de todas las peleas.");
/*  38*/            return "";
                }
/*  34*/        i++;
                  goto _L1
/*  40*/        i = 0;
_L3:
                int k;
/*  40*/        if(i >= ai.length)
/*  41*/            break MISSING_BLOCK_LABEL_109;
/*  41*/        k = 0;
_L2:
/*  41*/        if(k >= ai[i].length)
/*  43*/            break MISSING_BLOCK_LABEL_103;
/*  43*/        if(ai[i][k] != 1 && ai[i][k] != 2)
                {
/*  45*/            addFatalError("Los guerreros deben pertenecer al bando 1 o al bando 2.");
/*  46*/            return "";
                }
/*  41*/        k++;
                  goto _L2
/*  40*/        i++;
                  goto _L3
                int j;
/*  50*/        for(j = 1; 1 << j < N; j++);
/*  53*/        if(j != ai.length)
/*  55*/            return "Lamentablemente la soluci\363n no es correcta :(";
/*  57*/        k = 0;
_L5:
                int l;
/*  57*/        if(k >= N)
/*  58*/            break MISSING_BLOCK_LABEL_220;
/*  58*/        l = 0;
_L4:
/*  58*/        if(l >= k)
/*  60*/            break MISSING_BLOCK_LABEL_214;
/*  60*/        boolean flag = false;
/*  61*/        int i1 = 0;
/*  61*/        do
                {
/*  61*/            if(i1 >= ai.length)
/*  62*/                break;
/*  62*/            if(ai[i1][k] != ai[i1][l])
                    {
/*  64*/                flag = true;
/*  65*/                break;
                    }
/*  61*/            i1++;
                } while(true);
/*  67*/        if(!flag)
/*  69*/            return "Lamentablemente la soluci\363n no es correcta :(";
/*  58*/        l++;
                  goto _L4
/*  57*/        k++;
                  goto _L5
/*  72*/        return "El caso de prueba ha sido resuelto con \351xito :)";
                Exception exception;
/*  74*/        exception;
/*  75*/        System.err.println("Formato inv\341lido de respuesta.");
/*  76*/        exception.printStackTrace();
/*  77*/        return "";
            }

            int[][] bandos(int i)
                throws IOException
            {
                StringBuffer stringbuffer;
                BufferedReader bufferedreader;
                int j;
                int ai[][];
/*  89*/        try
                {
/*  89*/            if(proc == null)
/*  90*/                return new int[0][0];
                }
/* 112*/        catch(Exception exception)
                {
/* 114*/            System.err.println("Formato inv\341lido de respuesta.");
/* 115*/            exception.printStackTrace();
/* 116*/            return new int[0][0];
                }
/*  93*/        stringbuffer = new StringBuffer();
/*  94*/        stringbuffer.append(i).append('\n');
/*  95*/        os.write(stringbuffer.toString().getBytes());
/*  96*/        os.flush();
/*  99*/        bufferedreader = new BufferedReader(new InputStreamReader(is));
/* 100*/        j = Integer.parseInt(bufferedreader.readLine().split(" ")[0]);
/* 101*/        ai = new int[j][];
/* 102*/        for(int k = 0; k < j; k++)
                {
/* 104*/            String as[] = bufferedreader.readLine().split(" ");
/* 105*/            int l = as.length;
/* 106*/            ai[k] = new int[l];
/* 107*/            for(int i1 = 0; i1 < l; i1++)
/* 108*/                ai[k][i1] = Integer.parseInt(as[i1]);

                }

/* 110*/        return ai;
            }

            public KaioKenTester(String s)
            {
/* 123*/        try
                {
/* 123*/            if(exec != null)
/* 125*/                try
                        {
/* 125*/                    Runtime runtime = Runtime.getRuntime();
/* 126*/                    proc = runtime.exec(exec);
/* 127*/                    os = proc.getOutputStream();
/* 128*/                    is = proc.getInputStream();
/* 129*/                    br = new BufferedReader(new InputStreamReader(is));
/* 130*/                    (new ErrorReader(proc.getErrorStream())).start();
                        }
/* 131*/                catch(Exception exception)
                        {
/* 131*/                    exception.printStackTrace();
                        }
/* 133*/            System.out.println(runTest(s));
/* 134*/            if(proc != null)
/* 135*/                try
                        {
/* 135*/                    proc.destroy();
                        }
/* 136*/                catch(Exception exception1)
                        {
/* 136*/                    exception1.printStackTrace();
                        }
                }
/* 138*/        catch(Exception exception2)
                {
/* 138*/            exception2.printStackTrace();
                }
            }

            public static void main(String args[])
            {
/* 142*/        String s = "1";
/* 143*/        for(int i = 0; i < args.length; i++)
                {
/* 144*/            if(args[i].equals("-test"))
/* 145*/                s = args[++i];
/* 146*/            if(args[i].equals("-exec"))
/* 147*/                exec = args[++i];
                }

/* 149*/        KaioKenTester kaiokentester = new KaioKenTester(s);
            }

            void addFatalError(String s)
            {
/* 153*/        System.out.println(s);
            }

            int N;
            static String exec;
            static Process proc;
            InputStream is;
            OutputStream os;
            BufferedReader br;
}

