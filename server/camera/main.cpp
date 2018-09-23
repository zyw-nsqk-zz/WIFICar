#include "camera.h"
#include "server.h"
#include "internalconnection.h"
#include <QCoreApplication>
#include <QObject>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Camera cap;
	Server ser;
	InternalConnection internal;

	QObject::connect(&ser,		&Server::fatalError,				&a, &QCoreApplication::quit, Qt::QueuedConnection);
	QObject::connect(&internal,	&InternalConnection::fatalError,	&a, &QCoreApplication::quit, Qt::QueuedConnection);
	QObject::connect(&cap,		&Camera::fatalError,				&a, &QCoreApplication::quit, Qt::QueuedConnection);
	QObject::connect(&internal, &InternalConnection::cameraStateChanged, &cap, &Camera::cameraStateChanged, Qt::QueuedConnection);
	QObject::connect(&ser,		&Server::cameraStateChanged, &cap, &Camera::cameraStateChanged, Qt::QueuedConnection);
	QObject::connect(&cap,		&Camera::capturedImage, &ser, &Server::sendImage);

	cap.init();
	ser.init();
	internal.init();

	return a.exec();
}
