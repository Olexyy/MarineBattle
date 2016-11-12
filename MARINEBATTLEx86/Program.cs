using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Marine.Battle
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            MBForm Interface = new MBForm();
            MBCore Game      = new MBCore();
            Interface.RequestGenerateMap += Game.Generate_Map_Handler;
            Interface.RequestMap += Game.Request_Map_Handler;
            Interface.SendUserMove += Game.User_Move_Handler;
            Interface.SendPCMove += Game.PC_Move_Handler;
            Game.Send_Map += Interface.AcceptMapHandler;
            Game.Send_Results += Interface.AcceptResultHandler;
            Application.Run(Interface);
        }
    }
}
