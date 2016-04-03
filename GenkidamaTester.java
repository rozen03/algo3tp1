// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) lnc 
// Source File Name:   GenkidamaTester.java

import java.io.*;
import java.security.SecureRandom;
import java.util.Arrays;

public class GenkidamaTester
{

            void generate(String s)
            {
/*  17*/        try
                {
/*  17*/            SecureRandom securerandom = SecureRandom.getInstance("SHA1PRNG");
/*  18*/            long l = Long.parseLong(s);
/*  19*/            securerandom.setSeed(l);
/*  20*/            N = securerandom.nextInt(0x186a0) + 1;
/*  21*/            T = securerandom.nextInt(10000) + 1;
/*  22*/            x = new int[N];
/*  23*/            y = new int[N];
/*  24*/            for(int i = 0; i < N; i++)
                    {
/*  26*/                x[i] = securerandom.nextInt(0xf4240);
/*  27*/                y[i] = securerandom.nextInt(0xf4240);
                    }

/*  29*/            Arrays.sort(x);
/*  30*/            Arrays.sort(y);
/*  31*/            for(int j = 0; 2 * j < N; j++)
                    {
/*  33*/                int l1 = x[j];
/*  34*/                x[j] = x[N - 1 - j];
/*  35*/                x[N - 1 - j] = l1;
                    }

/*  37*/            for(int k = 0; k < N; k++)
/*  38*/                if((y[k] + N) - 1 - k >= 0xf4240)
/*  39*/                    y[k] = 0xf4240 - (N - 1 - k) - 1;

/*  40*/            for(int i1 = 1; i1 < N; i1++)
/*  42*/                if(y[i1] <= y[i1 - 1])
/*  43*/                    y[i1] = y[i1 - 1] + 1;

/*  45*/            for(int j1 = N - 1; j1 >= 0; j1--)
/*  46*/                if(x[j1] + j1 >= 0xf4240)
/*  47*/                    x[j1] = 0xf4240 - j1 - 1;

/*  48*/            for(int k1 = N - 2; k1 >= 0; k1--)
/*  50*/                if(x[k1] <= x[k1 + 1])
/*  51*/                    x[k1] = x[k1 + 1] + 1;

                }
/*  54*/        catch(Exception exception)
                {
/*  55*/            addFatalError("An exception occurred while trying to get your program's results.");
/*  56*/            exception.printStackTrace();
                }
            }

            int solve()
            {
/*  61*/        int i = 0;
/*  62*/        int j = -1;
/*  63*/        int k = 0;
/*  64*/        while(j < N - 1) 
                {
/*  66*/            k++;
/*  67*/            for(; i + 1 < N && cubre(i + 1, j + 1); i++);
/*  69*/            for(j = i; j < N - 1 && cubre(i, j + 1); j++);
/*  72*/            i = j + 1;
                }
/*  74*/        return k;
            }

            String getScore(int i)
            {
/*  77*/        int j = solve();
/*  78*/        if(i == j)
/*  79*/            return "El caso de prueba ha sido resuelto con \351xito :)";
/*  81*/        else
/*  81*/            return "Lamentablemente la soluci\363n no es correcta :(";
            }

            boolean cubre(int i, int j)
            {
/*  85*/        return x[i] + T >= x[j] && y[i] + T >= y[j];
            }

            public String runTest(String s)
            {
                int ai[];
                int i;
                int ai1[];
                int k;
                int l;
/*  90*/        try
                {
/*  90*/            generate(s);
/*  93*/            ai = indices(x, y, T);
/*  96*/            if(ai[0] + 1 != ai.length)
                    {
/*  98*/                addFatalError("La respuesta no coincide con la cantidad de enemigos en la salida del programa.");
/*  99*/                return "";
                    }
                }
/* 128*/        catch(Exception exception)
                {
/* 129*/            System.err.println("Formato inv\341lido de respuesta.");
/* 130*/            exception.printStackTrace();
/* 131*/            return "";
                }
/* 101*/        if(ai[0] < 1 || ai[0] > N)
                {
/* 103*/            addFatalError("La cantidad de Genkidamas debe ser un entero entre 1 y N, siendo N la cantidad de enemigos.");
/* 104*/            return "";
                }
/* 106*/        i = 1;
_L1:
/* 106*/        if(i >= ai.length)
/* 107*/            break MISSING_BLOCK_LABEL_107;
/* 107*/        if(ai[i] < 1 || ai[i] > N)
                {
/* 109*/            addFatalError("Cada \355ndice debe ser un entero entre 1 y N, siendo N la cantidad de enemigos.");
/* 110*/            return "";
                }
/* 106*/        i++;
                  goto _L1
/* 113*/        ai1 = new int[ai.length - 1];
/* 114*/        for(int j = 0; j < ai1.length; j++)
/* 115*/            ai1[j] = ai[j + 1];

/* 116*/        Arrays.sort(ai1);
/* 117*/        k = 0;
/* 118*/        l = 0;
_L2:
/* 118*/        if(l >= N)
/* 120*/            break MISSING_BLOCK_LABEL_203;
/* 120*/        for(; k < ai1.length && !cubre(ai1[k] - 1, l); k++);
/* 122*/        if(k == ai1.length)
/* 123*/            return "Lamentablemente la soluci\363n no es correcta :(";
/* 118*/        l++;
                  goto _L2
/* 125*/        String s1 = getScore(ai[0]);
/* 126*/        return s1;
            }

            int[] indices(int ai[], int ai1[], int i)
                throws IOException
            {
                StringBuffer stringbuffer;
                BufferedReader bufferedreader;
                int k;
                String as[];
                int l;
                int ai2[];
/* 143*/        try
                {
/* 143*/            if(proc == null)
/* 144*/                return new int[0];
                }
/* 165*/        catch(Exception exception)
                {
/* 167*/            System.err.println("Formato inv\341lido de respuesta.");
/* 168*/            exception.printStackTrace();
/* 169*/            return new int[0];
                }
/* 147*/        stringbuffer = new StringBuffer();
/* 148*/        stringbuffer.append(ai.length).append(' ').append(i).append('\n');
/* 149*/        for(int j = 0; j < ai.length; j++)
/* 150*/            stringbuffer.append((new StringBuilder()).append(ai[j]).append(" ").append(ai1[j]).toString()).append('\n');

/* 151*/        os.write(stringbuffer.toString().getBytes());
/* 152*/        os.flush();
/* 155*/        bufferedreader = new BufferedReader(new InputStreamReader(is));
/* 156*/        k = Integer.parseInt(bufferedreader.readLine().split(" ")[0]);
/* 157*/        as = bufferedreader.readLine().split(" ");
/* 158*/        l = as.length;
/* 159*/        ai2 = new int[l + 1];
/* 160*/        ai2[0] = k;
/* 161*/        for(int i1 = 1; i1 <= l; i1++)
/* 162*/            ai2[i1] = Integer.parseInt(as[i1 - 1]);

/* 163*/        return ai2;
            }

            public GenkidamaTester(String s)
            {
/* 176*/        try
                {
/* 176*/            if(exec != null)
/* 178*/                try
                        {
/* 178*/                    Runtime runtime = Runtime.getRuntime();
/* 179*/                    proc = runtime.exec(exec);
/* 180*/                    os = proc.getOutputStream();
/* 181*/                    is = proc.getInputStream();
/* 182*/                    br = new BufferedReader(new InputStreamReader(is));
/* 183*/                    (new ErrorReader(proc.getErrorStream())).start();
                        }
/* 184*/                catch(Exception exception)
                        {
/* 184*/                    exception.printStackTrace();
                        }
/* 186*/            System.out.println(runTest(s));
/* 187*/            if(proc != null)
/* 188*/                try
                        {
/* 188*/                    proc.destroy();
                        }
/* 189*/                catch(Exception exception1)
                        {
/* 189*/                    exception1.printStackTrace();
                        }
                }
/* 191*/        catch(Exception exception2)
                {
/* 191*/            exception2.printStackTrace();
                }
            }

            public static void main(String args[])
            {
/* 195*/        String s = "1";
/* 196*/        for(int i = 0; i < args.length; i++)
                {
/* 197*/            if(args[i].equals("-test"))
/* 198*/                s = args[++i];
/* 199*/            if(args[i].equals("-exec"))
/* 200*/                exec = args[++i];
                }

/* 202*/        GenkidamaTester genkidamatester = new GenkidamaTester(s);
            }

            void addFatalError(String s)
            {
/* 206*/        System.out.println(s);
            }

            int N;
            int T;
            int x[];
            int y[];
            static String exec;
            static Process proc;
            InputStream is;
            OutputStream os;
            BufferedReader br;
}

