namespace office2swf
{
    partial class ProjectInstaller
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.office2swfserviceProcessInstaller = new System.ServiceProcess.ServiceProcessInstaller();
            this.office2swfserviceInstaller = new System.ServiceProcess.ServiceInstaller();
            // 
            // office2swfserviceProcessInstaller
            // 
            this.office2swfserviceProcessInstaller.Account = System.ServiceProcess.ServiceAccount.LocalSystem;
            this.office2swfserviceProcessInstaller.Password = null;
            this.office2swfserviceProcessInstaller.Username = null;
            // 
            // office2swfserviceInstaller
            // 
            this.office2swfserviceInstaller.ServiceName = "office2wsfService";
            // 
            // ProjectInstaller
            // 
            this.Installers.AddRange(new System.Configuration.Install.Installer[] {
            this.office2swfserviceProcessInstaller,
            this.office2swfserviceInstaller});

        }

        #endregion

        private System.ServiceProcess.ServiceProcessInstaller office2swfserviceProcessInstaller;
        private System.ServiceProcess.ServiceInstaller office2swfserviceInstaller;
    }
}