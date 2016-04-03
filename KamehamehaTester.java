// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) lnc 
// Source File Name:   KamehamehaTester.java

import java.io.*;
import java.security.SecureRandom;
import java.util.*;

public class KamehamehaTester
{

            void generate(String s)
            {
/*  16*/        try
                {
/*  16*/            SecureRandom securerandom = SecureRandom.getInstance("SHA1PRNG");
/*  17*/            long l = Long.parseLong(s);
/*  18*/            securerandom.setSeed(l);
/*  19*/            N = securerandom.nextInt(8) + 3;
/*  20*/            int i = securerandom.nextInt(N) + 3;
/*  21*/            int ai[] = new int[i];
/*  22*/            int ai1[] = new int[i];
/*  23*/            int ai2[] = new int[i];
/*  24*/            ArrayList arraylist = new ArrayList();
/*  25*/            ArrayList arraylist1 = new ArrayList();
/*  26*/            ArrayList arraylist2 = new ArrayList();
/*  27*/            while(arraylist.size() < N) 
                    {
/*  29*/                arraylist.clear();
/*  30*/                arraylist1.clear();
/*  31*/                int j = 0;
/*  31*/                while(j < i) 
                        {
/*  33*/                    for(boolean flag = true; flag;)
                            {
/*  36*/                        flag = false;
/*  37*/                        if(arraylist.isEmpty() || securerandom.nextInt(3) <= 1)
                                {
/*  39*/                            ai[j] = securerandom.nextInt(201) - 100;
/*  40*/                            ai1[j] = securerandom.nextInt(201) - 100;
/*  41*/                            ai2[j] = securerandom.nextInt(201) - 100;
                                } else
                                {
/*  45*/                            ai[j] = securerandom.nextInt(201) - 100;
/*  46*/                            ai1[j] = securerandom.nextInt(201) - 100;
/*  47*/                            int k1 = securerandom.nextInt(arraylist.size());
/*  48*/                            ai2[j] = ai[j] * ((Integer)arraylist.get(k1)).intValue() - ai1[j] * ((Integer)arraylist1.get(k1)).intValue();
                                }
/*  50*/                        int l1 = 0;
/*  50*/                        while(l1 < j) 
                                {
/*  51*/                            if(ai[l1] * ai1[j] == ai[j] * ai1[l1] && ai2[j] == ai2[l1])
/*  52*/                                flag = true;
/*  50*/                            l1++;
                                }
                            }

/*  54*/                    int i2 = 0;
/*  55*/                    for(int l2 = 0; l2 < 1000; l2++)
                            {
/*  56*/                        for(int l3 = 0; l3 < 1000; l3++)
                                {
/*  57*/                            if(l2 * ai[j] != l3 * ai1[j] + ai2[j] || l2 == 0 && l3 == 0)
/*  59*/                                continue;
/*  59*/                            boolean flag1 = false;
/*  60*/                            for(int i4 = 0; i4 < arraylist.size(); i4++)
/*  61*/                                if(((Integer)arraylist.get(i4)).intValue() == l2 && ((Integer)arraylist1.get(i4)).intValue() == l3)
/*  62*/                                    flag1 = true;

/*  63*/                            if(!flag1)
                                    {
/*  65*/                                arraylist.add(Integer.valueOf(l2));
/*  66*/                                arraylist1.add(Integer.valueOf(l3));
/*  67*/                                i2++;
                                    }
                                }

                            }

/*  70*/                    if(i2 < 5)
                            {
/*  72*/                        j--;
/*  73*/                        for(int i3 = 0; i3 < i2; i3++)
                                {
/*  75*/                            arraylist.remove(arraylist.size() - 1);
/*  76*/                            arraylist1.remove(arraylist1.size() - 1);
                                }

                            }
/*  31*/                    j++;
                        }
                    }
/*  81*/            int k = 0;
/*  82*/            for(int i1 = 0; i1 < arraylist.size(); i1++)
                    {
/*  84*/                int j2 = 1;
/*  85*/                for(int j3 = 0; j3 < i; j3++)
/*  86*/                    if(ai[j3] * ((Integer)arraylist.get(i1)).intValue() == ai1[j3] * ((Integer)arraylist1.get(i1)).intValue() + ai2[j3] && j2 < 0xf4240)
/*  87*/                        j2 *= 50;

/*  88*/                k += j2;
/*  89*/                arraylist2.add(Integer.valueOf(j2));
                    }

/*  91*/            x = new int[N];
/*  92*/            y = new int[N];
/*  93*/            for(int j1 = 0; j1 < N; j1++)
                    {
/*  95*/                int k2 = securerandom.nextInt(k);
                        int k3;
/*  95*/                for(k3 = 0; k2 - ((Integer)arraylist2.get(k3)).intValue() > 0; k3++)
/*  98*/                    k2 -= ((Integer)arraylist2.get(k3)).intValue();

/* 101*/                k -= ((Integer)arraylist2.get(k3)).intValue();
/* 102*/                arraylist2.set(k3, Integer.valueOf(0));
/* 103*/                x[j1] = ((Integer)arraylist.get(k3)).intValue();
/* 104*/                y[j1] = ((Integer)arraylist1.get(k3)).intValue();
                    }

                }
/* 107*/        catch(Exception exception)
                {
/* 108*/            addFatalError("An exception occurred while trying to get your program's results.");
/* 109*/            exception.printStackTrace();
                }
            }

            boolean colineales(int i, int j, int k)
            {
/* 117*/        return (x[j] - x[i]) * (y[k] - y[i]) == (x[k] - x[i]) * (y[j] - y[i]);
            }

            void go(int i)
            {
/* 121*/        cant++;
/* 122*/        if(i == N)
                {
/* 124*/            res = Math.min(res, cant);
/* 125*/            cant--;
/* 126*/            return;
                }
/* 128*/        comp[i] = cant;
/* 129*/        boolean flag = false;
/* 130*/        for(int j = i + 1; j < N; j++)
                {
/* 131*/            if(comp[j] != -1)
/* 133*/                continue;
/* 133*/            flag = true;
/* 134*/            comp[j] = cant;
/* 135*/            for(int k = j + 1; k < N; k++)
/* 137*/                if(colineales(i, j, k))
/* 138*/                    comp[k] = cant;

/* 140*/            boolean flag1 = false;
/* 141*/            int l = i + 1;
/* 141*/            do
                    {
/* 141*/                if(l >= N)
/* 142*/                    break;
/* 142*/                if(comp[l] == -1)
                        {
/* 144*/                    go(l);
/* 145*/                    flag1 = true;
/* 146*/                    break;
                        }
/* 141*/                l++;
                    } while(true);
/* 148*/            if(!flag1)
/* 149*/                go(N);
/* 150*/            for(int i1 = j; i1 < N; i1++)
/* 151*/                if(comp[i1] == cant)
/* 152*/                    comp[i1] = -1;

/* 153*/            comp[j] = -1;
                }

/* 155*/        if(!flag)
/* 156*/            go(N);
/* 157*/        comp[i] = -1;
/* 158*/        cant--;
            }

            int solve()
            {
/* 163*/        comp = new int[N];
/* 164*/        for(int i = 0; i < N; i++)
/* 165*/            comp[i] = -1;

/* 166*/        cant = -1;
/* 167*/        res = N;
/* 168*/        go(0);
/* 169*/        return res;
            }

            String getScore(int i)
            {
/* 172*/        int j = solve();
/* 173*/        if(i == j)
/* 174*/            return "El caso de prueba ha sido resuelto con \351xito :)";
/* 176*/        else
/* 176*/            return "Lamentablemente la soluci\363n no es correcta :(";
            }

            public String runTest(String s)
            {
                int ai[][];
                HashSet hashset;
                int i;
                int j;
                int k;
                int l;
                int i1;
                int j1;
/* 181*/        try
                {
/* 181*/            generate(s);
/* 184*/            ai = rectas(x, y);
/* 187*/            if(ai.length > N)
                    {
/* 189*/                addFatalError("La cantidad de rectas de be ser menor o igual a N.");
/* 190*/                return "";
                    }
                }
/* 241*/        catch(Exception exception)
                {
/* 242*/            System.err.println("Formato inv\341lido de respuesta.");
/* 243*/            exception.printStackTrace();
/* 244*/            return "";
                }
/* 192*/        hashset = new HashSet();
/* 193*/        i = 0;
_L1:
/* 193*/        if(i >= ai.length)
/* 194*/            break MISSING_BLOCK_LABEL_90;
/* 194*/        if(ai[i].length < 1 || ai[i].length > N)
                {
/* 196*/            addFatalError("Las rectas deben contener entre 1 y N puntos.");
/* 197*/            return "";
                }
/* 193*/        i++;
                  goto _L1
/* 199*/        i = 0;
_L3:
/* 199*/        if(i >= ai.length)
/* 200*/            break MISSING_BLOCK_LABEL_204;
/* 200*/        j = 0;
_L2:
/* 200*/        if(j >= ai[i].length)
/* 202*/            break MISSING_BLOCK_LABEL_198;
/* 202*/        if(hashset.contains(Integer.valueOf(ai[i][j])))
                {
/* 204*/            addFatalError("Cada punto debe pertenecer a exactamente una recta.");
/* 205*/            return "";
                }
/* 207*/        if(ai[i][j] < 1 || ai[i][j] > N)
                {
/* 209*/            addFatalError("Los puntos son enumerados entre 1 y N.");
/* 210*/            return "";
                }
/* 212*/        hashset.add(Integer.valueOf(ai[i][j]));
/* 200*/        j++;
                  goto _L2
/* 199*/        i++;
                  goto _L3
/* 214*/        if(hashset.size() != N)
                {
/* 216*/            addFatalError("Entre todas las rectas deben estar exactamente todos los puntos una vez cada uno.");
/* 217*/            return "";
                }
/* 219*/        i = 0;
_L5:
/* 219*/        if(i >= ai.length)
/* 220*/            break MISSING_BLOCK_LABEL_396;
/* 220*/        if(ai[i].length < 3)
/* 222*/            break MISSING_BLOCK_LABEL_390;
/* 222*/        j = x[ai[i][0] - 1];
/* 223*/        k = y[ai[i][0] - 1];
/* 224*/        l = x[ai[i][1] - 1];
/* 225*/        i1 = y[ai[i][1] - 1];
/* 226*/        j1 = 2;
_L4:
/* 226*/        if(j1 >= ai[i].length)
/* 228*/            break MISSING_BLOCK_LABEL_390;
/* 228*/        int k1 = x[ai[i][j1] - 1];
/* 229*/        int l1 = y[ai[i][j1] - 1];
/* 230*/        if((l - j) * (l1 - k) != (k1 - j) * (i1 - k))
                {
/* 232*/            addFatalError("Cada recta deber ser efectivamente una recta, es decir, que sus puntos est\351n todos alineados.");
/* 233*/            return "";
                }
/* 226*/        j1++;
                  goto _L4
/* 219*/        i++;
                  goto _L5
/* 238*/        String s1 = getScore(ai.length);
/* 239*/        return s1;
            }

            public String checkData(String s)
            {
/* 249*/        return "";
            }

            public String displayTestCase(String s)
            {
/* 253*/        generate(s);
/* 254*/        StringBuffer stringbuffer = new StringBuffer();
/* 255*/        stringbuffer.append((new StringBuilder()).append("Test Case = ").append(s).append("\n").toString());
/* 256*/        stringbuffer.append((new StringBuilder()).append("N = ").append(N).toString());
/* 257*/        for(int i = 0; i < N; i++)
/* 258*/            stringbuffer.append((new StringBuilder()).append("(").append(x[i]).append(",").append(y[i]).append(") ").toString());

/* 259*/        return stringbuffer.toString();
            }

            public double[] score(double ad[][])
            {
/* 263*/        double ad1[] = new double[ad.length];
/* 265*/        for(int i = 0; i < ad.length; i++)
                {
/* 266*/            ad1[i] = 0.0D;
/* 267*/            for(int j = 0; j < ad[0].length; j++)
/* 268*/                ad1[i] += ad[i][j];

                }

/* 270*/        return ad1;
            }

            int[][] rectas(int ai[], int ai1[])
                throws IOException
            {
                StringBuffer stringbuffer;
                BufferedReader bufferedreader;
                int k;
                int ai2[][];
/* 281*/        try
                {
/* 281*/            if(proc == null)
/* 282*/                return new int[0][0];
                }
/* 306*/        catch(Exception exception)
                {
/* 308*/            System.err.println("Formato inv\341lido de respuesta.");
/* 309*/            exception.printStackTrace();
/* 310*/            return new int[0][0];
                }
/* 285*/        stringbuffer = new StringBuffer();
/* 286*/        stringbuffer.append(ai.length).append('\n');
/* 287*/        for(int i = 0; i < ai.length; i++)
/* 288*/            stringbuffer.append((new StringBuilder()).append(ai[i]).append(" ").append(ai1[i]).toString()).append('\n');

/* 289*/        os.write(stringbuffer.toString().getBytes());
/* 290*/        os.flush();
/* 293*/        bufferedreader = new BufferedReader(new InputStreamReader(is));
/* 294*/        k = Integer.parseInt(bufferedreader.readLine().split(" ")[0]);
/* 295*/        ai2 = new int[k][];
/* 296*/        for(int j = 0; j < k; j++)
                {
/* 298*/            String as[] = bufferedreader.readLine().split(" ");
/* 299*/            int l = Integer.parseInt(as[0]);
/* 300*/            ai2[j] = new int[l];
/* 301*/            for(int i1 = 1; i1 <= l; i1++)
/* 302*/                ai2[j][i1 - 1] = Integer.parseInt(as[i1]);

                }

/* 304*/        return ai2;
            }

            public KamehamehaTester(String s)
            {
/* 317*/        try
                {
/* 317*/            if(exec != null)
/* 319*/                try
                        {
/* 319*/                    Runtime runtime = Runtime.getRuntime();
/* 320*/                    proc = runtime.exec(exec);
/* 321*/                    os = proc.getOutputStream();
/* 322*/                    is = proc.getInputStream();
/* 323*/                    br = new BufferedReader(new InputStreamReader(is));
/* 324*/                    (new ErrorReader(proc.getErrorStream())).start();
                        }
/* 325*/                catch(Exception exception)
                        {
/* 325*/                    exception.printStackTrace();
                        }
/* 327*/            System.out.println(runTest(s));
/* 328*/            if(proc != null)
/* 329*/                try
                        {
/* 329*/                    proc.destroy();
                        }
/* 330*/                catch(Exception exception1)
                        {
/* 330*/                    exception1.printStackTrace();
                        }
                }
/* 332*/        catch(Exception exception2)
                {
/* 332*/            exception2.printStackTrace();
                }
            }

            public static void main(String args[])
            {
/* 336*/        String s = "1";
/* 337*/        for(int i = 0; i < args.length; i++)
                {
/* 338*/            if(args[i].equals("-test"))
/* 339*/                s = args[++i];
/* 340*/            if(args[i].equals("-exec"))
/* 341*/                exec = args[++i];
                }

/* 343*/        KamehamehaTester kamehamehatester = new KamehamehaTester(s);
            }

            void addFatalError(String s)
            {
/* 347*/        System.out.println(s);
            }

            int N;
            int x[];
            int y[];
            int comp[];
            int cant;
            int res;
            static String exec;
            static Process proc;
            InputStream is;
            OutputStream os;
            BufferedReader br;
}

