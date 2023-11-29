#include <iostream>
#include <chrono>
#include <cassert>
#include <faiss/utils.h>
#include <eigen3/Eigen/Dense>
#include <cblas.h>

void renorm(std::vector<float> &feat) {
    float l2_sum = 0;
    for (auto &f : feat) l2_sum += f * f;
    if (l2_sum < 1e-5) return;
    l2_sum = std::sqrt(l2_sum);
    for (auto &f : feat) f /= l2_sum;
}

std::mt19937 rng;
std::uniform_real_distribution<> distrib; // 默认[0, 1)

// l2 norm
void gen_matrixs(const int size, const int dim, std::vector<std::vector<float>> &feats) {
    for (int i = 0; i < size; ++i) {
        std::vector<float> feat;
        for (int j = 0; j < dim; ++j) {
            feat.push_back(distrib(rng));
        }
        renorm(feat);
        feats.push_back(feat);
    }
}

void get_ip_distance_by_faiss(const std::vector<std::vector<float>> &search_feats, const std::vector<std::vector<float>> &base_feats, std::vector<std::vector<float>> &dis) {
    std::vector<float> other_resize_feat;
    for (auto &feat : base_feats) {
        other_resize_feat.insert(other_resize_feat.end(), feat.begin(), feat.end());
    }
    int nx = search_feats.size();
    int ny = base_feats.size();
    int dim = search_feats.empty() ? 0 : search_feats[0].size();
    dis.resize(nx, std::vector<float>(ny, 0.0));
    auto t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < nx; ++i) {
        faiss::fvec_inner_products_ny(dis[i].data(), search_feats[i].data(), other_resize_feat.data(), dim, ny);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "faiss core code take " << std::chrono::duration<float>(t1 - t0).count() << std::endl;
}

void get_ip_distance_by_eigen(const Eigen::MatrixXf &search_feats, const Eigen::MatrixXf &base_feats, std::vector<std::vector<float>> &dis) {
    auto t0 = std::chrono::high_resolution_clock::now();
    Eigen::MatrixXf res_dis = search_feats * base_feats.transpose();
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "eigen core code take " << std::chrono::duration<float>(t1 - t0).count() << std::endl;
    dis.resize(res_dis.rows(), std::vector<float>(res_dis.cols(), 0.0));
    for (int i = 0; i < res_dis.rows(); i++) {
        for (int j = 0; j < res_dis.cols(); j++) {
            dis[i][j] = res_dis(i, j);
        }
    }
}

void get_ip_distance_by_cblas(const std::vector<std::vector<float>> &feats1, const std::vector<std::vector<float>> &feats2, std::vector<std::vector<float>> &dis) {
    // feats2 需要转置，转置后列数为feats2.size()
    int M = feats1.size();
    int N = feats2.size();
    int K = feats1[0].size();
    int lda = K;
    int ldb = K;
    int ldc = N;
    auto tt0 = std::chrono::high_resolution_clock::now();
    std::vector<float> A, B, C(M * N, 0.0);
    for (auto &feat : feats1) A.insert(A.end(), feat.begin(), feat.end());
    for (auto &feat : feats2) B.insert(B.end(), feat.begin(), feat.end());
    auto t0 = std::chrono::high_resolution_clock::now();
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, M, N, K, 1, A.data(), lda, B.data(), ldb, 0, C.data(), ldc);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "cblas core code take " << std::chrono::duration<float>(t1 - t0).count() << std::endl;
    dis.resize(M, std::vector<float>(N, 0.0));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            dis[i][j] = C[i * N + j];
        }
    }
    auto tt1 = std::chrono::high_resolution_clock::now();
    std::cout << "cblas prepare feats take " << std::chrono::duration<float>(t0- tt0).count()
            << "cblas fill res take " << std::chrono::duration<float>(tt1- t1).count()
            << std::endl;
}

int main () {
    std::vector<std::vector<float>> feat1, feat2;
    gen_matrixs(5000, 256, feat1);
    gen_matrixs(5000, 256, feat2);
    std::vector<std::vector<float>> dis_cblas, dis_faiss, dis_eigen;
    {
        std::cout << "cblas get distance start" << std::endl;
        auto t0 = std::chrono::high_resolution_clock::now();
        get_ip_distance_by_cblas(feat1, feat2, dis_cblas);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "cblas get distance take " << std::chrono::duration<float>(t1 - t0).count() << std::endl;
        std::cout << std::endl;
    }
    {
        std::cout << "faiss get distance start" << std::endl;
        auto t0 = std::chrono::high_resolution_clock::now();
        get_ip_distance_by_faiss(feat1, feat2, dis_faiss);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "faiss get distance take " << std::chrono::duration<float>(t1 - t0).count() << std::endl;
        std::cout << std::endl;
    }
    {
        Eigen::MatrixXf feat1_eigen(feat1.size(), feat1[0].size());
        Eigen::MatrixXf feat2_eigen(feat2.size(), feat2[0].size());
        for (int i = 0; i < feat1_eigen.rows(); ++i) 
            for (int j = 0; j < feat1_eigen.cols(); ++j) 
                feat1_eigen(i, j) = feat1[i][j];
        for (int i = 0; i < feat2_eigen.rows(); ++i) 
            for (int j = 0; j < feat2_eigen.cols(); ++j) 
                feat2_eigen(i, j) = feat2[i][j];
        std::cout << "eigen get distance start" << std::endl;
        auto t0 = std::chrono::high_resolution_clock::now();
        get_ip_distance_by_eigen(feat1_eigen, feat2_eigen, dis_eigen);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "eigen get distance take " << std::chrono::duration<float>(t1 - t0).count() << std::endl;
        std::cout << std::endl;
    }
    std::cout << "check result" << std::endl;
    // #define DEBUG
    for (int i = 0; i < feat1.size(); ++i) {
        for (int j = 0; j < feat2.size(); ++j) {
            #ifdef DEBUG
            if (!(fabs(dis_cblas[i][j] - dis_faiss[i][j]) < 1e-5)) {
                std::cout << i << "," << j << " cblas dis " << dis_cblas[i][j] << " faiss dis " << dis_faiss[i][j] << std::endl;
            }
            if (!(fabs(dis_faiss[i][j] - dis_eigen[i][j]) < 1e-5)) {
                std::cout << i << "," << j << " faiss dis " << dis_cblas[i][j] << " eigen dis " << dis_faiss[i][j] << std::endl;
            }
            #endif
            assert(fabs(dis_cblas[i][j] - dis_faiss[i][j]) < 1e-5);
            assert(fabs(dis_faiss[i][j] - dis_eigen[i][j]) < 1e-5);
        }
    }
    std::cout << "all method to get distance are same" << std::endl;
    return 0;
}