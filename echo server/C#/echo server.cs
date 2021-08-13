using System;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace EchoServer
{
    class MainApp
    {
        static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                Console.WriteLine("���� : {0} <Bind IP>",
                    Process.GetCurrentProcess().ProcessName);
                return;
            }

            string bindIp = args[0];
            const int bindPort = 5425;
            TcpListener server = null;
            try
            {
                IPEndPoint localAddress =
                    new IPEndPoint(IPAddress.Parse(bindIp), bindPort);

                server = new TcpListener(localAddress);

                server.Start();

                Console.WriteLine("�޾Ƹ� ���� ����... ");

                while (true)
                {
                    TcpClient client = server.AcceptTcpClient();
                    Console.WriteLine("Ŭ���̾�Ʈ ���� : {0} ",
                        ((IPEndPoint)client.Client.RemoteEndPoint).ToString());

                    NetworkStream stream = client.GetStream();

                    int length;
                    string data = null;
                    byte[] bytes = new byte[256];

                    while ((length = stream.Read(bytes, 0, bytes.Length)) != 0)
                    {
                        data = Encoding.Default.GetString(bytes, 0, length);
                        Console.WriteLine(String.Format("����: {0}", data));

                        byte[] msg = Encoding.Default.GetBytes(data);

                        stream.Write(msg, 0, msg.Length);
                        Console.WriteLine(String.Format("�۽�: {0}", data));
                    }

                    stream.Close();
                    client.Close();
                }
            }
            catch (SocketException e)
            {
                Console.WriteLine(e);
            }
            finally
            {
                server.Stop();
            }

            Console.WriteLine("������ �����մϴ�.");
        }
    }
}