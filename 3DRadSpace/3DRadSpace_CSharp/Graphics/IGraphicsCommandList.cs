using Engine3DRadSpace.Math;

namespace Engine3DRadSpace.Graphics
{
    public interface IGraphicsCommandList : IPtrWrapper
    {
        public void Clear(Color clearColor);
		public void ClearRenderTarget(IRenderTarget rt, Color color);
		public void ClearDepthBuffer(IDepthStencilBuffer depth);

		public void SetViewport();
		public void SetViewport(Viewport viewport);

		public void SetViewports(Span<Viewport> viewports);
		public Viewport GetViewport();

		public void SetRenderTarget(IRenderTarget renderTarget);

		public void UnbindRenderTargetAndDepth();

		public void UnbindDepthBuffer();

		public void SetRenderTargetAndDepth(IRenderTarget renderTarget, IDepthStencilBuffer depthBuffer);

		public void SetRenderTargetAndDisableDepth(IRenderTarget renderTarget);

		public void DrawVertexBuffer(IVertexBuffer vertexBuffer, uint startSlot = 0);
		public void DrawVertexBufferWithindices(IVertexBuffer vertexBuffer, IIndexBuffer indexBuffer);
		public void DrawVertexBufferWithindices(IVertexBuffer vertexBuffer, IIndexBuffer indexBuffer, uint numIndices);

		public void SetShader(IShader shader);

		public void SetRasterizerState(IRasterizerState state);

        public void SetDepthStencilBuffer(IDepthStencilBuffer depthBuffer);
		public void SetDepthStencilState(IDepthStencilState depthState, uint reference);

		public void SetBlendState(IBlendState blendState, Color blendFactor, uint sampleMask = 0xFFFFFFFF);

        public void SetTopology(VertexTopology topology);
		public void DrawAuto();
		public void Present();

		public void SaveBackBufferToFile(string path);

		public void ResizeBackBuffer(System.Drawing.Point newResolution);
		public void ToggleFullScreen();
		public void Copy(IGPUBuffer dest, IGPUBuffer src);
    }
}
