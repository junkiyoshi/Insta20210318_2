#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	float phi_deg_step = 8;
	float theta_deg_step = 8;
	float noise_param = 0.5;
	float threshold = 0.5;
	float radius = 300;

	for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

		for (float theta_deg = theta_deg_step; theta_deg < 180; theta_deg += theta_deg_step) {

			auto noise_value = ofNoise(cos(phi_deg * DEG_TO_RAD) * noise_param, sin(phi_deg * DEG_TO_RAD) * noise_param, cos(theta_deg * DEG_TO_RAD) * noise_param, ofGetFrameNum() * 0.01);
			if (noise_value < threshold) { continue; }

			auto noise_1 = ofNoise(cos(phi_deg * DEG_TO_RAD) * noise_param, sin(phi_deg * DEG_TO_RAD) * noise_param, cos((theta_deg - theta_deg_step) * DEG_TO_RAD) * noise_param, ofGetFrameNum() * 0.01);
			auto noise_2 = ofNoise(cos((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_param, sin((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_param, cos(theta_deg * DEG_TO_RAD) * noise_param, ofGetFrameNum() * 0.01);
			auto noise_3 = ofNoise(cos((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_param, sin((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_param, cos(theta_deg * DEG_TO_RAD) * noise_param, ofGetFrameNum() * 0.01);
			auto noise_4 = ofNoise(cos(phi_deg * DEG_TO_RAD) * noise_param, sin(phi_deg * DEG_TO_RAD) * noise_param, cos((theta_deg + theta_deg_step) * DEG_TO_RAD) * noise_param, ofGetFrameNum() * 0.01);

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));

			this->face.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
			this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

			for (int k = 0; k < 4; k++) {

				this->face.addColor(ofColor(39));
				this->frame.addColor(ofColor(239));
			}

			if (noise_1 < threshold) {

				this->frame.addVertex(vertices[0]);
				this->frame.addVertex(vertices[1]);

				this->frame.addIndex(this->frame.getNumVertices() - 1);
				this->frame.addIndex(this->frame.getNumVertices() - 2);
			}

			if (noise_2 < threshold) {

				this->frame.addVertex(vertices[0]);
				this->frame.addVertex(vertices[2]);

				this->frame.addIndex(this->frame.getNumVertices() - 1);
				this->frame.addIndex(this->frame.getNumVertices() - 2);
			}

			if (noise_3 < threshold) {

				this->frame.addVertex(vertices[1]);
				this->frame.addVertex(vertices[3]);

				this->frame.addIndex(this->frame.getNumVertices() - 1);
				this->frame.addIndex(this->frame.getNumVertices() - 2);
			}

			if (noise_4 < threshold) {

				this->frame.addVertex(vertices[2]);
				this->frame.addVertex(vertices[3]);

				this->frame.addIndex(this->frame.getNumVertices() - 1);
				this->frame.addIndex(this->frame.getNumVertices() - 2);

			}
		}
	}

	radius = 150;

	for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

		for (float theta_deg = theta_deg_step; theta_deg < 180; theta_deg += theta_deg_step) {

			auto noise_value = ofNoise(cos(phi_deg * DEG_TO_RAD) * noise_param, sin(phi_deg * DEG_TO_RAD) * noise_param, cos(theta_deg * DEG_TO_RAD) * noise_param, ofGetFrameNum() * 0.01);
			if (noise_value > threshold) { continue; }

			auto noise_1 = ofNoise(cos(phi_deg * DEG_TO_RAD) * noise_param, sin(phi_deg * DEG_TO_RAD) * noise_param, cos((theta_deg - theta_deg_step) * DEG_TO_RAD) * noise_param, ofGetFrameNum() * 0.01);
			auto noise_2 = ofNoise(cos((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_param, sin((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_param, cos(theta_deg * DEG_TO_RAD) * noise_param, ofGetFrameNum() * 0.01);
			auto noise_3 = ofNoise(cos((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_param, sin((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_param, cos(theta_deg * DEG_TO_RAD) * noise_param, ofGetFrameNum() * 0.01);
			auto noise_4 = ofNoise(cos(phi_deg * DEG_TO_RAD) * noise_param, sin(phi_deg * DEG_TO_RAD) * noise_param, cos((theta_deg + theta_deg_step) * DEG_TO_RAD) * noise_param, ofGetFrameNum() * 0.01);

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));

			this->face.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
			this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

			for (int k = 0; k < 4; k++) {

				this->face.addColor(ofColor(39));
				this->frame.addColor(ofColor(239));
			}

			if (noise_1 > threshold) {

				this->frame.addVertex(vertices[0]);
				this->frame.addVertex(vertices[1]);

				this->frame.addIndex(this->frame.getNumVertices() - 1);
				this->frame.addIndex(this->frame.getNumVertices() - 2);
			}

			if (noise_2 >  threshold) {

				this->frame.addVertex(vertices[0]);
				this->frame.addVertex(vertices[2]);

				this->frame.addIndex(this->frame.getNumVertices() - 1);
				this->frame.addIndex(this->frame.getNumVertices() - 2);
			}

			if (noise_3 > threshold) {

				this->frame.addVertex(vertices[1]);
				this->frame.addVertex(vertices[3]);

				this->frame.addIndex(this->frame.getNumVertices() - 1);
				this->frame.addIndex(this->frame.getNumVertices() - 2);
			}

			if (noise_4 > threshold) {

				this->frame.addVertex(vertices[2]);
				this->frame.addVertex(vertices[3]);

				this->frame.addIndex(this->frame.getNumVertices() - 1);
				this->frame.addIndex(this->frame.getNumVertices() - 2);

			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.37);
	ofRotateY(ofGetFrameNum() * 0.72);

	this->frame.draw();
	this->face.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}