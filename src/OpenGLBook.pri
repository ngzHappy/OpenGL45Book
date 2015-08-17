TEMPLATE = subdirs
#.file
#.depends

APPVoidTest.file = $$PWD/VoidTest/VoidTest.pro

LIBAssimp.file = $$PWD/OpenGLTool/ProjectAssimp/LibAssimp.pro
LIBAssimp.depends += APPVoidTest

SLIBOpenGLTool.file = $$PWD/OpenGLTool/OpenGLTool.pro
SLIBOpenGLTool.depends += LIBAssimp

APPProjectModel.file = $$PWD/ProjectModel/ProjectModel.pro
APPProjectModel.depends += SLIBOpenGLTool

APPProjectModelFlipTextureY.file = $$PWD/ProjectModelFlipTextureY/ProjectModelFlipTextureY.pro
APPProjectModelFlipTextureY.depends += SLIBOpenGLTool

APPProjectModelFlipZ.file = $$PWD/ProjectModelFlipZ/ProjectModelFlipZ.pro
APPProjectModelFlipZ.depends += SLIBOpenGLTool

APPProjectModelFlipZTextureY.file = $$PWD/ProjectModelFlipZTextureY/ProjectModelFlipZTextureY.pro
APPProjectModelFlipZTextureY.depends += SLIBOpenGLTool

APPTemplateApplicaton.file = $$PWD/TemplateApplicaton/TemplateApplicaton.pro
APPTemplateApplicaton.depends += SLIBOpenGLTool

APPSimpleBuffer.file = $$PWD/SimpleBuffer/SimpleBuffer.pro
APPSimpleBuffer.depends += SLIBOpenGLTool

APPSimpleClear.file = $$PWD/SimpleClear/SimpleClear.pro
APPSimpleClear.depends += SLIBOpenGLTool

APPSimpleDebug.file = $$PWD/SimpleDebug/SimpleDebug.pro
APPSimpleDebug.depends += SLIBOpenGLTool

APPSimpleClearWithTimer.file = $$PWD/SimpleClearWithTimer/SimpleClearWithTimer.pro
APPSimpleClearWithTimer.depends += SLIBOpenGLTool

APPSinglePoint.file = $$PWD/SinglePoint/SinglePoint.pro
APPSinglePoint.depends += SLIBOpenGLTool

APPSingleTriangle.file = $$PWD/SingleTriangle/SingleTriangle.pro
APPSingleTriangle.depends += SLIBOpenGLTool

APPSingleTriangleWithTimer.file = $$PWD/SingleTriangleWithTimer/SingleTriangleWithTimer.pro
APPSingleTriangleWithTimer.depends += SLIBOpenGLTool

APPSingleCube.file = $$PWD/SingleCube/SingleCube.pro
APPSingleCube.depends += SLIBOpenGLTool

APPSimpleImageShow.file = $$PWD/SimpleImageShow/SimpleImageShow.pro
APPSimpleImageShow.depends += SLIBOpenGLTool

APPSimpleTextureArray.file = $$PWD/SimpleTextureArray/SimpleTextureArray.pro
APPSimpleTextureArray.depends += SLIBOpenGLTool

APPSimpleDrawArrays.file=$$PWD/SimpleDrawArrays/SimpleDrawArrays.pro
APPSimpleDrawArrays.depends += SLIBOpenGLTool

APPSimpleDrawArraysInstanced.file=$$PWD/SimpleDrawArraysInstanced/SimpleDrawArraysInstanced.pro
APPSimpleDrawArraysInstanced.depends += SLIBOpenGLTool

APPSimpleDrawArraysInstancedBaseInstance.file=$$PWD/SimpleDrawArraysInstancedBaseInstance/SimpleDrawArraysInstancedBaseInstance.pro
APPSimpleDrawArraysInstancedBaseInstance.depends += SLIBOpenGLTool

APPSimpleDrawElements.file=$$PWD/SimpleDrawElements/SimpleDrawElements.pro
APPSimpleDrawElements.depends += SLIBOpenGLTool

APPSimpleDrawElementsBaseVertex.file=$$PWD/SimpleDrawElementsBaseVertex/SimpleDrawElementsBaseVertex.pro
APPSimpleDrawElementsBaseVertex.depends += SLIBOpenGLTool

APPSimpleDrawElementsInstanced.file=$$PWD/SimpleDrawElementsInstanced/SimpleDrawElementsInstanced.pro
APPSimpleDrawElementsInstanced.depends += SLIBOpenGLTool

APPSimpleDrawElementsInstancedBaseInstance.file=$$PWD/SimpleDrawElementsInstancedBaseInstance/SimpleDrawElementsInstancedBaseInstance.pro
APPSimpleDrawElementsInstancedBaseInstance.depends += SLIBOpenGLTool

APPSimpleDrawElementsInstancedBaseVertex.file=$$PWD/SimpleDrawElementsInstancedBaseVertex/SimpleDrawElementsInstancedBaseVertex.pro
APPSimpleDrawElementsInstancedBaseVertex.depends += SLIBOpenGLTool

APPSimpleDrawElementsInstancedBaseVertexBaseInstance.file=$$PWD/SimpleDrawElementsInstancedBaseVertexBaseInstance/SimpleDrawElementsInstancedBaseVertexBaseInstance.pro
APPSimpleDrawElementsInstancedBaseVertexBaseInstance.depends += SLIBOpenGLTool

APPSimpleDrawRangeElements.file=$$PWD/SimpleDrawRangeElements/SimpleDrawRangeElements.pro
APPSimpleDrawRangeElements.depends += SLIBOpenGLTool

APPSimpleDrawRangeElementsBaseVertex.file=$$PWD/SimpleDrawRangeElementsBaseVertex/SimpleDrawRangeElementsBaseVertex.pro
APPSimpleDrawRangeElementsBaseVertex.depends += SLIBOpenGLTool

APPSimpleLoadModel.file=$$PWD/SimpleLoadModel/SimpleLoadModel.pro
APPSimpleLoadModel.depends += SLIBOpenGLTool

APPSimpleDepthTest.file=$$PWD/SimpleDepthTest/SimpleDepthTest.pro
APPSimpleDepthTest.depends += SLIBOpenGLTool

APPSimpleMultiSampleFBO.file=$$PWD/SimpleMultiSampleFBO/SimpleMultiSampleFBO.pro
APPSimpleMultiSampleFBO.depends += SLIBOpenGLTool

APPSimpleFBO.file=$$PWD/SimpleFBO/SimpleFBO.pro
APPSimpleFBO.depends += SLIBOpenGLTool

APPNormalSphere.file = $$PWD/NormalSphere/NormalSphere.pro
APPNormalSphere.depends += SLIBOpenGLTool

APPRotateNormalSphere.file= $$PWD/RotateNormalSphere/RotateNormalSphere.pro
APPRotateNormalSphere.depends+=SLIBOpenGLTool

APPSpider.file= $$PWD/Spider/Spider.pro
APPSpider.depends+=SLIBOpenGLTool

APPModelView.file= $$PWD/ModelView/ModelView.pro
APPModelView.depends+=SLIBOpenGLTool

APPSimpleComputeShader.file= $$PWD/SimpleComputeShader/SimpleComputeShader.pro
APPSimpleComputeShader.depends+=SLIBOpenGLTool

SUBDIRS += APPVoidTest
SUBDIRS += LIBAssimp
SUBDIRS += SLIBOpenGLTool
SUBDIRS += APPProjectModel
SUBDIRS += APPProjectModelFlipZTextureY
SUBDIRS += APPProjectModelFlipZ
SUBDIRS += APPProjectModelFlipTextureY
SUBDIRS += APPTemplateApplicaton
SUBDIRS += APPSimpleBuffer
SUBDIRS += APPSimpleClear
SUBDIRS += APPSimpleDebug
SUBDIRS += APPSimpleClearWithTimer
SUBDIRS += APPSinglePoint
SUBDIRS += APPSingleTriangle
SUBDIRS += APPSingleTriangleWithTimer
SUBDIRS += APPSingleCube
SUBDIRS += APPSimpleImageShow
SUBDIRS += APPSimpleTextureArray
SUBDIRS += APPSimpleDrawArrays
SUBDIRS += APPSimpleDrawArraysInstanced
SUBDIRS += APPSimpleDrawArraysInstancedBaseInstance
SUBDIRS += APPSimpleDrawElements
SUBDIRS += APPSimpleDrawElementsBaseVertex
SUBDIRS += APPSimpleDrawElementsInstanced
SUBDIRS += APPSimpleDrawElementsInstancedBaseInstance
SUBDIRS += APPSimpleDrawElementsInstancedBaseVertex
SUBDIRS += APPSimpleDrawElementsInstancedBaseVertexBaseInstance
SUBDIRS += APPSimpleDrawRangeElements
SUBDIRS += APPSimpleDrawRangeElementsBaseVertex
SUBDIRS += APPSimpleLoadModel
SUBDIRS += APPSimpleDepthTest
SUBDIRS += APPSimpleFBO
SUBDIRS += APPSimpleMultiSampleFBO
SUBDIRS += APPNormalSphere
SUBDIRS += APPRotateNormalSphere
SUBDIRS += APPSpider
SUBDIRS += APPModelView
SUBDIRS += APPSimpleComputeShader








